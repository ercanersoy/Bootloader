/************************************************
 * Ercan Ersoy's Bootloader Strings Header File *
 ************************************************/

#include "configurations.h"

#define EN 1
#define TR 2

#if STRINGS_LANGUAGE == 1  // English
   #define BOOTLOADER_NAME "Ercan Ersoy's Bootlaoder"
   #define STRING_FIRMWARE_TO_UPLOAD "Firmware to upload:"
#elif STRINGS_LANGUAGE == 2  // Turkish
   #define BOOTLOADER_NAME "Ercan Ersoy'un Önyükleyicisi"
   #define STRING_FIRMWARE_TO_UPLOAD "Yüklenecek bellenim:"
#endif
