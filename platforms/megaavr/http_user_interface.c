/*******************************************************************
 * Ercan Ersoy's Bootloader ATmega HTTP User Interface Source File *
 *******************************************************************/

#ifdef __AVR__
   #ifdef __AVR_MEGA__
      #if USER_INTERFACE_TYPE == HTTP
         #include "../../main.h"

const char strings_1[] PROGMEM = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nContent-Length: ";
const char strings_2[] PROGMEM = "\r\n<html><head><meta charset=\"utf-8\" /> <title>";
const char strings_3[] PROGMEM = BOOTLOADER_NAME;
const char strings_4[] PROGMEM = " ";
const char strings_5[] PROGMEM = VERSION;
const char strings_6[] PROGMEM = "</title><body><h1>";
const char strings_7[] PROGMEM = BOOTLOADER_NAME;
const char strings_8[] PROGMEM = "</h1><p>";
const char strings_9[] PROGMEM = STRING_FIRMWARE_TO_UPLOAD;
const char strings_10[] PROGMEM = "</p><form enctype=\"multipart/form-data\" method=\"POST\">";
const char strings_11[] PROGMEM = "<input type=\"file\" name=\"firmware\" /><input type=\"submit\" /></form></html>\r\n";

const char* const strings[] PROGMEM = {strings_1, strings_2, strings_3, strings_4, strings_3, strings_5, strings_6, strings_7, strings_8, strings_9, strings_10, strings_11};

int i = 0;  // Counter
uint16_t content_length = 0;  // Page content length
char buffer_1[SPM_PAGESIZE + 1] = "\0";  // First buffer
char content_length_string[6] = {'\0', '\0', '\0', '\0', '\0', '\0'};  // Content length string
char *buffer_1_pointer;  // First buffer's pointer
char buffer_2[2] = "\0";  // Second buffer
uint16_t received_size = 0;  // Receive
uint8_t network_status = 0;  // Network status
int16_t substring = 0;  // Index of substring
char boundary[64];  // Boundary buffer
uint8_t boundary_size = 0;  //  Boundary size
uint8_t user_interface_status = 0;  // User interface status (0 = read boundary, 1 = read content-length, 2 = read boundary, 3 - 6 = read new line, 7 = calculate read size, 8 = read_program)
int j = 0;  // Counter
uint8_t page = 0;  // Page counter

int8_t http_getting_value(char* method, char buffer[], char value[], uint8_t value_length)
{
   char *pointer;  // Buffer's pointer
   char read_buffer[2];  // Read buffer
   int16_t buffer_substring;  // Buffer's substring index

   buffer_substring = substring_index(buffer, method);
   if(buffer_substring >= 0)
   {
      pointer = buffer;
      network_receive(read_buffer, 1);
      while(*read_buffer != '\r')
      {
         *pointer = *read_buffer;
         pointer++;
         *pointer= '\0';

         network_receive(read_buffer, 1);  // Read character
      }

      strncpy(value, buffer, value_length);  // Copy value
      pointer = buffer;
      *buffer = '\0';

      received_size = network_received_size();  // Get received size
      
      return buffer_substring;
   }
   
   return -1;
}

void clear_buffer(void)
{
   int k;  // Counter

   for(k = 0; k < SPM_PAGESIZE; k++)
   {
      buffer_1[k] = 0xFF;  // Clear buffer_1
   }
}

void boot_write_page(uint32_t page, uint8_t *buffer)
{
    int k;  // Counter
    uint16_t word;  // Word

    eeprom_busy_wait ();
    boot_page_erase (page);
    boot_spm_busy_wait ();

    for (k = 0; k < SPM_PAGESIZE; k += 2)
    {
        word = buffer[k];
        word += buffer[k + 1] << 8;

        boot_page_fill (page + k, word);
    }

    boot_page_write (page);
    boot_spm_busy_wait();
    boot_rww_enable ();
}

void user_interface_main(void)
{
   for(i = 0; i < 9; i++)
   {
      content_length += strlen_P((char *)pgm_read_word(&(strings[i])));  // Calculate content length
   }

   for(i = 0; i < 9; i++)
   {
      strcpy_P(buffer_1, (char *)pgm_read_word(&(strings[i])));  // Read from program memory
      network_transmit(buffer_1, strlen_P((char *)pgm_read_word(&(strings[i]))));  // Transmit data

      if(i == 0)
      {
         network_transmit(integer_to_string(content_length, content_length_string), 3);  // Transmit content length
         network_transmit("\r\n", 2);  // Transmit end line
      }
   }

   network_disconnect();

   while(1)
   {
      network_status = network_device_register_read_byte(0x0403);  // Reading status register

      if(network_status == 0x00)  // If socket closed
      {
         if(network_device_register_read_byte(0x0403) == 0x00)
         {
            network_close();  // Network socket close
         }

         network_device_register_write_byte(0x0400, 0x01);  // Network open

         network_device_register_write_byte(0x0404, ((USER_INTERFACE_PORT & 0xFF00) >> 8));  // Writting TCP port
         network_device_register_write_byte(0x0405, USER_INTERFACE_PORT & 0x00FF);  // Writting TCP port
         network_device_register_write_byte(0x0401, 0x01);  // Write open command to command register

         while(network_device_register_read_byte(0x0401));  // Wait writting command

         if(network_device_register_read_byte(0x0403) == 0x13)  // If socket initialzition
         {
            if(network_listen() <= 0)
            {
               _delay_ms(1);
            }
         }
      }
      else if(network_status == 0x17)  // If socket established
      {
         received_size = network_received_size();  // Get received size

         if(received_size > 0)
         {
            network_receive(buffer_1, 32);  // Reading first 32 bytes of HTTP request

            substring = substring_index(buffer_1, "POST /");
            if(substring >= 0)
            {
               *buffer_1 == '\0';
               buffer_1_pointer = buffer_1;

               while(received_size > 0)
               {
                  substring = -1;

                  network_receive(buffer_2, 1);  // Reading character

                  if(*buffer_2 != '\r' && *buffer_2 != '\n')  // If not netwline
                  {
                     *buffer_1_pointer = *buffer_2;
                     buffer_1_pointer++;
                     *buffer_1_pointer = '\0';
                     
                     if(user_interface_status == 3)
                     {
                        content_length--;  // Calculate content_length
                     }
                     else if(user_interface_status == 4)
                     {
                        content_length--;  // Calculate content_length
                     }
                     else if(user_interface_status == 5)
                     {
                        content_length--;  // Calculate content_length
                     }
                     else if(user_interface_status == 6)
                     {
                        content_length--;  // Calculate content_length
                     }
                  }
                  else
                  {
                     if(*buffer_2 == '\r' && user_interface_status >= 3 && user_interface_status <= 6)
                     {
                        content_length--;  // Calculate content_length
                     }
                     else if(*buffer_2 == '\n' && user_interface_status >= 3 && user_interface_status <= 6)
                     {
                        content_length--;  // Calculate content_length
                        user_interface_status++;
                     }
                     
                     *buffer_1 = '\0';
                     buffer_1_pointer = buffer_1;
                  }

                  if(user_interface_status == 0 && http_getting_value("Content-Type: multipart/form-data; boundary=", buffer_1, boundary, 61) >= 0)
                  {
                     user_interface_status++;  // Readed Content-Type

                     continue;
                  }

                  if(user_interface_status == 1 && http_getting_value("Content-Length: ", buffer_1, content_length_string, 5) >= 0)
                  {
                     content_length = string_to_integer(content_length_string);
                     if(content_length >= 0)
                     {
                        for(i = 63; i > 1; i++)
                        {
                           boundary[i] = boundary[i - 2];  // Shift boundary buffer
                        }

                        boundary[0] = '-';
                        boundary[1] = '-';

                        user_interface_status++;  // Readed Content-Length
                     }
                     else
                     {
                        break;
                     }
                  }

                  substring = substring_index(buffer_1, boundary);
                  if(user_interface_status == 2 && substring >= 0)
                  {
                     substring = -1;

                     boundary_size = strlen(boundary);    // Calculate boundary size

                     content_length -= boundary_size;  // Calculate content_length

                     buffer_1[0] = '\0';
                     buffer_1_pointer = buffer_1;

                     user_interface_status++;

                     goto end_loop;
                  }

                  if(user_interface_status == 7)
                  {
                     content_length -= (boundary_size + 10);  // Calculate content_length

                     user_interface_status++;
                     
                     goto end_loop;
                  }
                  
                  if(user_interface_status == 8 && content_length != 0)
                  {
                     clear_buffer();

                     buffer_1[0] = buffer_2[j];  // Copy character into main buffer

                     j = 1;
                     page = 0;
                     
                     for(i = 0; i < content_length; i++)
                     {
                        network_receive(buffer_2, 1);  // Read character
                        buffer_1[j] = buffer_2[0];  // Copy character into main buffer

                        j++;
                        
                        if(j == SPM_PAGESIZE || i + 1 == content_length)
                        {
                           boot_write_page(page, buffer_1);  // Write porgram memory
                           page += SPM_PAGESIZE;

                           clear_buffer();
                           j = 0;
                        }
                     }
                     
                     break;
                  }

                  end_loop:

                  received_size = network_received_size();    // Get received size
               }
            }

            network_disconnect();  // Network socket disconnect
            network_close();  // Network socket close

            goto *APPLICATION_START;

         }
         else
         {
            _delay_us(10);
         }
      }
      else if(network_status == 0x18 || network_status == 0x1A || network_status == 0x1B || network_status == 0x1C || network_status == 0x1D)  // If connection termination
      {
         network_close();  // Network socket close
      }
   }
}
      #endif
   #endif
#endif
