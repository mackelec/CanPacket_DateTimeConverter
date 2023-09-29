#include "CanPacket_DateTimeConverter.h"
#include <cstring>  // for using strlen and strncmp

CanPacket_DateTimeConverter::CanPacket_DateTimeConverter() {
    prepareDateTimeCanPacket(__DATE__, __TIME__);
}

void CanPacket_DateTimeConverter::setDateTime(const char* date, const char* time) {
    prepareDateTimeCanPacket(date, time);
}

void CanPacket_DateTimeConverter::toStrings(char* dateStr, char* timeStr) {
    canPacketToDateAndTime(dateStr, timeStr);
}

void CanPacket_DateTimeConverter::prepareDateTimeCanPacket(const char* compileDate, const char* compileTime) {
    if (compileDate == NULL || compileTime == NULL) return;

    // Parse Year
    int year = (compileDate[7] - '0') * 1000 + (compileDate[8] - '0') * 100 + (compileDate[9] - '0') * 10 + (compileDate[10] - '0');
    canPacket[0] = year >> 8; // high byte
    canPacket[1] = year & 0xFF; // low byte

    // Parse Month
    canPacket[2] = getMonthfromDate(compileDate);

    // Parse Day
    canPacket[3] = (compileDate[4] == ' ' ? 0 : (compileDate[4] - '0') * 10) + (compileDate[5] - '0');

    // Parse Time: hours, minutes, and seconds
    canPacket[4] = (compileTime[0] - '0') * 10 + (compileTime[1] - '0');
    canPacket[5] = (compileTime[3] - '0') * 10 + (compileTime[4] - '0');
    canPacket[6] = (compileTime[6] - '0') * 10 + (compileTime[7] - '0');

    // Set Extra Byte
    canPacket[7] = 0x00;
}

void CanPacket_DateTimeConverter::canPacketToDateAndTime(char* dateStr, char* timeStr) {
    int year = (canPacket[0] << 8) | canPacket[1];
    byte month = canPacket[2];
    byte day = canPacket[3];

    // Extract Time: Hours, Minutes, and Seconds
    byte hours = canPacket[4];
    byte minutes = canPacket[5];
    byte seconds = canPacket[6];

    // Convert to String Format
    snprintf(dateStr, 12, "%s %02d %04d", getMonthString(month), day, year);
    snprintf(timeStr, 9, "%02d:%02d:%02d", hours, minutes, seconds);
}

byte CanPacket_DateTimeConverter::getMonthfromDate(const char* month) {
    if(month == NULL || strlen(month) != 3) return 0;

    if(strncmp(month, "Jan", 3) == 0) return 1;
    if(strncmp(month, "Feb", 3) == 0) return 2;
    if(strncmp(month, "Mar", 3) == 0) return 3;
    if(strncmp(month, "Apr", 3) == 0) return 4;
    if(strncmp(month, "May", 3) == 0) return 5;
    if(strncmp(month, "Jun", 3) == 0) return 6;
    if(strncmp(month, "Jul", 3) == 0) return 7;
    if(strncmp(month, "Aug", 3) == 0) return 8;
    if(strncmp(month, "Sep", 3) == 0) return 9;
    if(strncmp(month, "Oct", 3) == 0) return 10;
    if(strncmp(month, "Nov", 3) == 0) return 11;
    if(strncmp(month, "Dec", 3) == 0) return 12;

    return 0;
}

const char* CanPacket_DateTimeConverter::getMonthString(byte month) {
    switch(month) {
        case 1: return "Jan";
        case 2: return "Feb";
        case 3: return "Mar";
        case 4: return "Apr";
        case 5: return "May";
        case 6: return "Jun";
        case 7: return "Jul";
        case 8: return "Aug";
        case 9: return "Sep";
        case 10: return "Oct";
        case 11: return "Nov";
        case 12: return "Dec";
        default: return "???";
    }
}
