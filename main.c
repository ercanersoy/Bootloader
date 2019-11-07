/*********************************************
 * Ercan Ersoy's Bootloader Main Source File *
 *********************************************/

#ifndef __GNUC__
   #error The software must be compiled by GCC.
#endif

#include "main.h"

void main(void)
{
#ifdef ETHERNET_ADAPTER_ENABLE
   network_initialization();  // Ethernet adapter inintialization
#endif

   while(SWITCH_PORT & (1 << SWTICH_PIN) == 1)
   {
      if(network_device_register_read_byte(0x0403) == 0x17)  // Wait for connection established
      {
         user_interface_main();  // User interface
      }
   }

   goto *APPLICATION_START;  // Start application
   return;
}
