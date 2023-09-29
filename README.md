# CanPacket_DateTimeConverter
Arduino library intended to create a 8 byte array for a CAN Packet, to represent date and time, aimed at providing a compiled __DATE__ and __TIME__

###  Example

```
#include "DateTimeConverter.h"

DateTimeConverter dateTimeConverter;

void setup() {
    Serial.begin(9600);
    dateTimeConverter.setDateTime("Sep 30 2023", "18:45:30");
    // dateTimeConverter.setDateTime(__DATE__, __TIME__); // Uncomment to set to compile date and time
    Serial.print(F("Directly Accessed CanPacket: "));
    for(byte i = 0; i < 8; i++) {
        Serial.print(dateTimeConverter.canPacket[i], HEX);
    }
    Serial.println();

    char dateStr[12];
    char timeStr[9];
    dateTimeConverter.toStrings(dateStr, timeStr);

    Serial.print(F("Converted Date: "));
    Serial.println(dateStr);
    Serial.print(F("Converted Time: "));
    Serial.println(timeStr);
}

void loop() {
    // Nothing to do here
}

```
