Ercan Ersoy's Bootloader 0.2

  All rights belong to Ercan Ersoy. This software is licensed by GNU LGPL v3.
  Ercan Ersoy's bootloader is being developed for microcontrollers. Program
  uploading is perfomed over HTTP. Currently only this bootloader is being
  developed for ATmega328 and equivalent microcontrollers from microcontrollers
  in AVR architecture.

Configurations:

  Ercan Ersoy's bootloader 0.1 is configured by configurations.h file.
  Configurations are listed below:

  - STRINGS_LANGUAGE -> Language of strings
  - UART_ENABLE -> Set UART driver is enabled
  - UART_BAUD_RATE -> Set UART Baud rate
  - ETHERNET_ADAPTER_ENABLE -> Enable Ethernet adapter driver
  - ETHERNET_ADAPTER -> Type of Ethernet
  - ETHERNET_ADAPTER_PORT_MODE_ADDRESS -> Ethernet adapter chip selection port
    mode address
  - ETHERNET_ADAPTER_PORT_ADDRESS -> Ethernet adapter chip selection port
    address
  - ETHERNET_ADAPTER_CHIP_SELECTION -> Ethernet adapter chip selection pin
  - SWITCH_PORT -> Switch port address
  - SWTICH_PIN -> Switch pin
  - USER_INTERFACE_TYPE -> User interface type
  - USER_INTERFACE_PORT -> User interface socket port
  - HARDWARE_MAC_ADDRESS_1, HARDWARE_MAC_ADDRESS_2, HARDWARE_MAC_ADDRESS_3,
    HARDWARE_MAC_ADDRESS_4, HARDWARE_MAC_ADDRESS_5, HARDWARE_MAC_ADDRESS_6 ->
    MAC address of network adapter
  - SOURCE_IP_ADDRESS_1, SOURCE_IP_ADDRESS_2, SOURCE_IP_ADDRESS_3,
    SOURCE_IP_ADDRESS_4 -> Network adapter IP address
  - SUBNET_MASK_1, SUBNET_MASK_2, SUBNET_MASK_3, SUBNET_MASK_4 -> Network
    adapter subnet mask
  - GATEWAY_IP_ADDRESS_1, GATEWAY_IP_ADDRESS_2, GATEWAY_IP_ADDRESS_3,
    GATEWAY_IP_ADDRESS_4 -> Network adapter gateway IP address

Compiling and installing:

  Compile options, linking options and writting program memory options
  on Makefile. Useable Makefile options are listed below:

  - all -> Compile Ercan Ersoy's bootloader
  - install -> Upload Ercan Ersoy's bootloader to microcontroller
  - set-fuses -> Set microcontroller fuse bits
  - clean -> Clean binaries and objects
  - clean-objects -> Clean objects only

  Default uploader is USBtinyISP.

Usage:

  For view HTTP user interface on browser, required supply logic one
  determinated switch pin and after, send request on via web browser.

  For supplying logic one, you could use a switch.

  Default network adapter IP address is 192.168.0.5.
  Default subnet mask is 255.255.255.0.
  Default gateway IP address is 192.168.0.1.
  Default socket port is 8000.

  Ercan Ersoy's bootloader is tested on Mozilla Firefox.

Verison History:

  * 0.2 (12-04-2020): Add .gitignore and README.md files.
                      The license changed to MIT License.
                      Updated README.txt files.

  * 0.1 (08-08-2019): Initial version
