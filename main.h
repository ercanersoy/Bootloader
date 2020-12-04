/*********************************************
 * Ercan Ersoy's Bootloader Main Header File *
 *********************************************/

#ifdef __AVR__
   #ifdef __AVR_MEGA__
      #include <avr/boot.h>
      #include <avr/io.h>
      #include <avr/interrupt.h>
      #include <avr/pgmspace.h>
      #include <stdint.h>
      #include <stdlib.h>
      #include <string.h>
      #include <util/delay.h>
   #endif
#endif

#include "configurations.h"
#include "strings.h"

#define VERSION "0.2"  // Version information

void starting_message(void);  // Starting message prortotype

// Standart library functions prototypes
char* integer_to_string(uint16_t, char*);
uint16_t string_to_integer(char *);
int16_t substring_index(char *, char *);

// UART functions prototpye
void uart_initialization(void);
void uart_write_character(char);
void uart_write_character_array(char *);
void uart_close(void);

// Network functions prototypes
uint8_t network_device_register_read_byte(uint16_t);
void network_device_register_write_byte(uint16_t, uint8_t);
uint8_t network_listen(void);
void network_disconnect(void);
void network_close(void);
void network_initialization(void);
void network_transmit(char *, uint16_t);
void network_receive(char *, uint16_t);
uint16_t network_received_size(void);

// Interrupt functions prototypes
void interrupt_enable(void);
void interrupt_disable(void);

// User interface prototypes
void user_interface_main(void);

#ifdef __AVR__
   #ifdef __AVR_MEGA__
      #define APPLICATION_START 0
   #endif 
#endif
