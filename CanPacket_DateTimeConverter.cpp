#include "CanPacket_DateTimeConverter.h"
#include <cstring>  // for using strlen and strncmp


    /*
    CAN Packet Byte Structure:
    [0] - Years since 2000
    [1] - Month (1-12)
    [2] - Day (1-31)
    [3] - Hour (0-23)
    [4] - Minute (0-59)
    [5] - Second (0-59)
    [6] - Reserved
    [7] - Reserved
    */





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

    // Parse Year and convert to years since 2000
    int year_since_2000 = ((compileDate[7] - '0') * 1000 + (compileDate[8] - '0') * 100 + (compileDate[9] - '0') * 10 + (compileDate[10] - '0')) - 2000;
    canPacket[0] = year_since_2000;  // Years since 2000

    // Parse Month
    canPacket[1] = getMonthfromDate(&compileDate[0]);  // Month

    // Parse Day
    canPacket[2] = (compileDate[4] == ' ' ? 0 : (compileDate[4] - '0') * 10) + (compileDate[5] - '0');  // Day

    // Parse Time: hours, minutes, and seconds
    canPacket[3] = (compileTime[0] - '0') * 10 + (compileTime[1] - '0');  // Hour
    canPacket[4] = (compileTime[3] - '0') * 10 + (compileTime[4] - '0');  // Minute
    canPacket[5] = (compileTime[6] - '0') * 10 + (compileTime[7] - '0');  // Second

    // Set Extra Bytes (for future use or extensions)
    canPacket[6] = 0x00;
    canPacket[7] = 0x00;
}

void CanPacket_DateTimeConverter::canPacketToDateAndTime(char* dateStr, char* timeStr) {
    int full_year = 2000 + canPacket[0];
    byte month = canPacket[1];
    byte day = canPacket[2];

    // Extract Time: Hours, Minutes, and Seconds
    byte hours = canPacket[3];
    byte minutes = canPacket[4];
    byte seconds = canPacket[5];

    // Convert to String Format
    snprintf(dateStr, 12, "%s %02d %04d", getMonthString(month), day, full_year);
    snprintf(timeStr, 9, "%02d:%02d:%02d", hours, minutes, seconds);
}

byte CanPacket_DateTimeConverter::getMonthfromDate(const char* monthStr) {
    if(monthStr == NULL) return 0;

    if(strncmp(monthStr, "Jan", 3) == 0) return 1;
    if(strncmp(monthStr, "Feb", 3) == 0) return 2;
    if(strncmp(monthStr, "Mar", 3) == 0) return 3;
    if(strncmp(monthStr, "Apr", 3) == 0) return 4;
    if(strncmp(monthStr, "May", 3) == 0) return 5;
    if(strncmp(monthStr, "Jun", 3) == 0) return 6;
    if(strncmp(monthStr, "Jul", 3) == 0) return 7;
    if(strncmp(monthStr, "Aug", 3) == 0) return 8;
    if(strncmp(monthStr, "Sep", 3) == 0) return 9;
    if(strncmp(monthStr, "Oct", 3) == 0) return 10;
    if(strncmp(monthStr, "Nov", 3) == 0) return 11;
    if(strncmp(monthStr, "Dec", 3) == 0) return 12;

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
