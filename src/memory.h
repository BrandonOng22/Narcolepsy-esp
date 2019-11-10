#include "Arduino.h"
#include <EEPROM.h>

uint const ADDRESS = 0;

size_t const MEMORY_SIZE = 8;

static struct{
    int sw = 0;
    int seg = 0;
} settings;

void updateSettings(int sw, int seg);

void initializeSettings();