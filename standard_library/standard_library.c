/*********************************************************
 * Ercan Ersoy's Bootloader Standard Library Source File *
 *********************************************************/

#include "../main.h"

char* integer_to_string(uint16_t integer, char buffer[]){
    char const digit[] = "0123456789";
    char *temporary = buffer;
    int shifter = integer;

   do
   {
      temporary++;
      shifter = shifter / 10;
   }while(shifter);

    *temporary = '\0';

   do
   {
      temporary--;
      *temporary = digit[integer % 10];
      integer = integer / 10;
   }
   while(integer);

   return buffer;
}

uint16_t string_to_integer(char buffer[])
{
    uint16_t multiple = 1;
    uint16_t result = 0;
    int string_length = strlen(buffer);
    
    for(int i = string_length -1 ; i >= 0 ; i--)
    {
        result = result + ((int)buffer[i] - 48) * multiple;
        multiple = multiple * 10;
    }
    return result;
}

int16_t substring_index(char *string, char *substring)
{
   uint8_t i = 0;
   uint8_t string_length = 0;
   
   string_length = strlen(substring);
   
   for(i = 0; *(string + i); i++)
   {
      if(!strncmp(string + i, substring, string_length))
      {
         return i;
      }
   }
   
   return -1;
}
