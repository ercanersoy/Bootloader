/****************************************************
 * Ercan Ersoy's Bootloader ATmega UART Source File *
 ****************************************************/

#ifdef __AVR__
   #ifdef __AVR_MEGA__

      #include "../../main.h"

      #if UART_ENABLE == 1

         #define BAUDRATE (F_CPU / UART_BAUD_RATE / 16)

void uart_initialization(void)  // UART initialization function
{
   UBRR0H = (BAUDRATE >> 8);
   UBRR0L = BAUDRATE;
   UCSR0B |= (1 << TXEN0);
}

void uart_write_character(char character)  // UART write character function
{
   while (!( UCSR0A & (1 << UDRE0)));
   UDR0 = character;
}

void uart_write_character_array(char *character_array)  // UART write character array function
{
   while(*character_array != '\0')
   {
      uart_write_character(*character_array);
      character_array++;
   }
}

void uart_close(void)  // UART ending function
{
   UCSR0B |= (0 << TXEN0) | (0 << RXEN0);
}
      #endif
   #endif
#endif
