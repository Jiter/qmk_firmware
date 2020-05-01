#include "jiter.h"

void rgb_change_color(void) {

    rgblight_sethsv_range(HSV_GREEN, 0, RGBLED_NUM);
    rgblight_set(); // Utility functions do not call rgblight_set() automatically, so they need to be called explicitly.
}