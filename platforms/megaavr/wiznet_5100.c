/***********************************************************
 * Ercan Ersoy's Bootloader ATmega Wiznet 5100 Source File *
 ***********************************************************/

#ifdef __AVR__
   #ifdef __AVR_MEGA__

      #include "../../main.h"

      #if ETHERNET_ADAPTER_ENABLE == 1
         #if ETHERNET_ADAPTER == DEVICE_WIZNET_5100

uint8_t network_device_register(uint16_t address, uint8_t byte, uint8_t opcode)
{
   ETHERNET_ADAPTER_PORT_ADDRESS &= ~(1 << ETHERNET_ADAPTER_CHIP_SELECTION);  // CS pin enable

   // Write write command
   SPDR = opcode;   
   while(!(SPSR & (1 << SPIF)));

   // Write higher bytes of address
   SPDR = (address & 0xFF00) >> 8;  
   while(!(SPSR & (1 << SPIF)));

   // Write lower bytes of address
   SPDR = address & 0x00FF;
   while(!(SPSR & (1 << SPIF)));

   // Write byte
   SPDR = byte;
   while(!(SPSR & (1 << SPIF)));

   ETHERNET_ADAPTER_PORT_ADDRESS |= (1 << ETHERNET_ADAPTER_CHIP_SELECTION);  // CS pin disable
   
   return SPDR;
}

void network_device_register_write_byte(uint16_t address, uint8_t byte)
{
   network_device_register(address, byte, 0xF0);
}

uint8_t network_device_register_read_byte(uint16_t address)
{
   return network_device_register(address, 0, 0x0F);
}

uint8_t network_listen(void)
{
   if(network_device_register_read_byte(0x403) == 0x13)
   {
      network_device_register_write_byte(0x401, 0x02);  // Network socket listen

      while(network_device_register_read_byte(0x401));  // Wait listening

      if(network_device_register_read_byte(0x403) == 0x14)  // If listening
      {
         return 1;
      }
      else
      {
         network_close();  // Network socket close
      }
   }

   return 0;
}

void network_disconnect(void)
{
   network_device_register_write_byte(0x0401, 0x08);  // Write disconnect command

   while(network_device_register_read_byte(0x0401));
}

void network_close(void)
{
   network_device_register_write_byte(0x0401, 0x10);  // Write disconnect command
   
   while(network_device_register_read_byte(0x0401));
}

void network_initialization(void)  // Network initialization function
{
   uint8_t hardware_mac_address[] = { HARDWARE_MAC_ADDRESS_1, HARDWARE_MAC_ADDRESS_2, HARDWARE_MAC_ADDRESS_3, HARDWARE_MAC_ADDRESS_4, HARDWARE_MAC_ADDRESS_5, HARDWARE_MAC_ADDRESS_6 };
   uint8_t source_ip_address[] = { SOURCE_IP_ADDRESS_1, SOURCE_IP_ADDRESS_2, SOURCE_IP_ADDRESS_3, SOURCE_IP_ADDRESS_4 };
   uint8_t subnet_mask[] = { SUBNET_MASK_1, SUBNET_MASK_2, SUBNET_MASK_3, SUBNET_MASK_4 };
   uint8_t gateway_ip_address[] = { GATEWAY_IP_ADDRESS_1, GATEWAY_IP_ADDRESS_2, GATEWAY_IP_ADDRESS_3, GATEWAY_IP_ADDRESS_4 };
   uint16_t network_socket_port = USER_INTERFACE_PORT;

   // Initialization pins and SPI
   DDRB = (1 << PORTB3) | (1 << PORTB5);
   ETHERNET_ADAPTER_PORT_MODE_ADDRESS |= (1 << ETHERNET_ADAPTER_CHIP_SELECTION);
   ETHERNET_ADAPTER_PORT_ADDRESS |= (1 << ETHERNET_ADAPTER_CHIP_SELECTION);
   SPCR = (1 << SPE) | (1 << MSTR);
   SPSR |= (1 << SPI2X);

   // Master mode
   network_device_register_write_byte(0x00, 0x80);
   _delay_ms(1);

   // Write gateway IP address
   network_device_register_write_byte(0x01, gateway_ip_address[0]);
   network_device_register_write_byte(0x02, gateway_ip_address[1]);
   network_device_register_write_byte(0x03, gateway_ip_address[2]);
   network_device_register_write_byte(0x04, gateway_ip_address[3]);
   _delay_ms(1);

   // Write subnet mask
   network_device_register_write_byte(0x05, subnet_mask[0]);
   network_device_register_write_byte(0x06, subnet_mask[1]);
   network_device_register_write_byte(0x07, subnet_mask[2]);
   network_device_register_write_byte(0x08, subnet_mask[3]);
   _delay_ms(1);

   // Write Hardware MAC address
   network_device_register_write_byte(0x09, hardware_mac_address[0]);
   network_device_register_write_byte(0x0A, hardware_mac_address[1]);
   network_device_register_write_byte(0x0B, hardware_mac_address[2]);
   network_device_register_write_byte(0x0C, hardware_mac_address[3]);
   network_device_register_write_byte(0x0D, hardware_mac_address[4]);
   network_device_register_write_byte(0x0E, hardware_mac_address[5]);
   _delay_ms(1);

   // Write soucre IP address
   network_device_register_write_byte(0x0F, source_ip_address[0]);
   network_device_register_write_byte(0x10, source_ip_address[1]);
   network_device_register_write_byte(0x11, source_ip_address[2]);
   network_device_register_write_byte(0x12, source_ip_address[3]);
   _delay_ms(1);

   // Write buffer size settings
   network_device_register_write_byte(0x1A, 0x55);
   network_device_register_write_byte(0x1B, 0x55);
   _delay_ms(1);

   socket_start:

   network_device_register_write_byte(0x400, 0x01);  // Set TCP mode

   network_device_register_write_byte(0x404, (network_socket_port & 0xFF00) >> 8);  // Setting socket port
   network_device_register_write_byte(0x405, network_socket_port & 0x00FF);  // Setting socket port

   network_device_register_write_byte(0x401, 0x1);  // Network socket open

   if(network_device_register_read_byte(0x403) != 0x13)  // If not TCP mode
   {
      network_device_register_write_byte(0x401, 0x10);  

      goto socket_start;
   }
   
   if(network_listen() == 0)
   {
      goto socket_start;
   }
}

void network_transmit(char *buffer, uint16_t buffer_size)
{
   uint16_t tx_size = 0;  // Write bytes size
   uint16_t offset_address = 0;  // Offset address of write buffer
   uint16_t real_address = 0;  // Real address of write buffer

   tx_size = ((network_device_register_read_byte(0x0420) & 0x00FF) << 8) + network_device_register_read_byte(0x0421);  // Read TX size

   while(tx_size < buffer_size)
   {
      _delay_ms(1);

      tx_size = ((network_device_register_read_byte(0x0420) & 0x00FF) << 8) + network_device_register_read_byte(0x0421);  // Read TX size
   }

   offset_address = (( network_device_register_read_byte(0x0424) & 0x00FF) << 8) + network_device_register_read_byte(0x0425);  // Read offset address

   while(buffer_size)
   {
      real_address = 0x4000 + (offset_address & 0x7FF);  // Calculate real address
      network_device_register_write_byte(real_address, *buffer);  // Write buffer

      buffer_size--;

      offset_address++;
      buffer++;
   }

   network_device_register_write_byte(0x0424, (offset_address & 0xFF00) >> 8);  // Write offset address
   network_device_register_write_byte(0x0425, (offset_address & 0x00FF));  // Write offset address

   network_device_register_write_byte(0x0401, 0x20);  // Write send command

   while(network_device_register_read_byte(0x0401));
}

void network_receive(char *buffer, uint16_t buffer_size)
{   
   uint16_t offset_address = 0;  // Offset address of read buffer
   uint16_t real_address = 0;  // Real address of read buffer
   
   offset_address = (( network_device_register_read_byte(0x0428) & 0x00FF) << 8) + network_device_register_read_byte(0x0429);  // Read offset address

   while(buffer_size)
   {
      real_address = 0x6000 + (offset_address & 0x7FF);  // Calculate real address
      *buffer = (char)network_device_register_read_byte(real_address);  // Write buffer

      buffer_size--;

      offset_address++;
      buffer++;
   }
   *buffer = '\0';

   network_device_register_write_byte(0x0428, (offset_address & 0xFF00) >> 8);  // Write offset address
   network_device_register_write_byte(0x0429, (offset_address & 0x00FF));  // Write offset address

   network_device_register_write_byte(0x0401, 0x40);
   _delay_us(5);
}

uint16_t network_received_size(void)  // Calculate received size function
{
   uint16_t value_1 = 0;
   uint16_t value_2 = 0;

   do
   {
      value_1 = (network_device_register_read_byte(0x426) << 8) + network_device_register_read_byte(0x0427);
      if (value_1 != 0)
      {
        value_2 = (network_device_register_read_byte(0x426) << 8) + network_device_register_read_byte(0x0427);
      }
   }while (value_1 != value_2);
   
   return value_2;
}
         #endif
      #endif
   #endif
#endif
