/******************************************************
 * Ercan Ersoy's Bootloader Configuration Header File *
 ******************************************************/

// Main Configurations

#define STRINGS_LANGUAGE EN


// Driver Configurations

#define UART_ENABLE 0
#define UART_BAUD_RATE 19200

#define ETHERNET_ADAPTER_ENABLE 1
#define ETHERNET_ADAPTER DEVICE_WIZNET_5100
#define ETHERNET_ADAPTER_PORT_MODE_ADDRESS DDRB
#define ETHERNET_ADAPTER_PORT_ADDRESS PORTB
#define ETHERNET_ADAPTER_CHIP_SELECTION PORTB2


// Switch Configurations

#define SWITCH_PORT PINC
#define SWTICH_PIN PC0

// User Interface Configurations

#define USER_INTERFACE_TYPE HTTP
#define USER_INTERFACE_PORT 8000

// Network Configurations

#define HARDWARE_MAC_ADDRESS_1 0x00
#define HARDWARE_MAC_ADDRESS_2 0x16
#define HARDWARE_MAC_ADDRESS_3 0x36
#define HARDWARE_MAC_ADDRESS_4 0xDE
#define HARDWARE_MAC_ADDRESS_5 0x58
#define HARDWARE_MAC_ADDRESS_6 0xF6

#define SOURCE_IP_ADDRESS_1 192
#define SOURCE_IP_ADDRESS_2 168
#define SOURCE_IP_ADDRESS_3 0
#define SOURCE_IP_ADDRESS_4 5

#define SUBNET_MASK_1 255
#define SUBNET_MASK_2 255
#define SUBNET_MASK_3 255
#define SUBNET_MASK_4 0

#define GATEWAY_IP_ADDRESS_1 192
#define GATEWAY_IP_ADDRESS_2 168
#define GATEWAY_IP_ADDRESS_3 0
#define GATEWAY_IP_ADDRESS_4 1
