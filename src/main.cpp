#include <Arduino.h>

#include "Arduino.h"
#include "bluetooth.h"
#include "memory.h"
#include <EEPROM.h>

struct{
    int sw = 0;
    int seg = 0;
} set;

void setup() {

  Serial.begin(115200);

  
  
  
  EEPROM.begin(MEMORY_SIZE);
  EEPROM.get(ADDRESS,set);
  Serial.println(set.sw);
  Serial.println("Old values are: "+String(set.sw)+","+String(set.seg));

  setupBluetooth();

}



void loop() {

  delay(2000);

}