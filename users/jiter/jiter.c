#include "jiter.h"
#include "rgblight.h"

void rgb_change_color(uint8_t hue, uint8_t sat, uint8_t val) {
    rgblight_sethsv_eeprom_helper(hue, sat, val, 1);
    rgblight_set(); // Utility functions do not call rgblight_set() automatically, so they need to be called explicitly.
}