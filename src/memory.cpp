#include "memory.h"

void updateSettings(int sw, int seg){
    if(settings.sw != sw || settings.seg != seg){
        settings.sw = sw;
        settings.seg = seg;
        EEPROM.put(ADDRESS,settings);
    }
}

void initializeSettings(){
    EEPROM.begin(MEMORY_SIZE);
    EEPROM.get(ADDRESS,settings);
    Serial.println(settings.sw);
}