# CanPacket_DateTimeConverter
Arduino library intended to create a 8 byte array for a CAN Packet, to represent date and time, aimed at providing a compiled __DATE__ and __TIME__

###  Example

```
#include "CanPacket_DateTimeConverter.h"

CanPacket_DateTimeConverter dateTimeConverter;

void setup() {
    Serial.begin(9600);

    // the class is loaded with __DATE__ and __TIME__  (date time of compilation)
    // at instantiation

    // next line is optional.  
    dateTimeConverter.setDateTime("Sep 30 2023", "18:45:30"); 

    byte *canData = dateTimeConverter.canPacket;
    // Modify the bytes as needed
    canData[0] = newByteValue; // Replace with the index and value you want to assign.

    // Print the modified canPacket
    Serial.print(F("Directly Accessed and Modified CanPacket: "));
    for(byte i = 0; i < 8; i++)
        Serial.print(canData[i], HEX);
    Serial.println();

    //  how to reference the byte array
    byte *canData = dateTimeConverter.canPacket;
    // Modify the bytes as needed
    // canData[0] = newByteValue; 

    // to perform the reverse operation
    // received array back to Date Time

    char dateStr[12];
    char timeStr[9];
    dateTimeConverter.toStrings(dateStr, timeStr); 

    Serial.print(F("Converted Date: "));
    Serial.println(dateStr);
    Serial.print(F("Converted Time: "));
    Serial.println(timeStr);
}

void loop() {
    // No operation in loop
}


```
