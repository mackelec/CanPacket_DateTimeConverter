#ifndef CanPacket_DateTimeConverter_h
#define CanPacket_DateTimeConverter_h

#include "Arduino.h"

class CanPacket_DateTimeConverter {
public:
    CanPacket_DateTimeConverter();
    void toStrings(char* dateStr, char* timeStr);
    void setDateTime(const char* date, const char* time);
    byte canPacket[8];

private:
    void prepareDateTimeCanPacket(const char* compileDate, const char* compileTime);
    void canPacketToDateAndTime(char* dateStr, char* timeStr);
    byte getMonthfromDate(const char* month);
    const char* getMonthString(byte month);
};

#endif
