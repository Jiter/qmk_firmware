#include "jiter.h"


#ifdef NEO2_ENABLE
// These indicate if left and right shift are physically pressed
bool lshift = false;
bool rshift = false;

// Interrupt and times for space cadet shift
bool lshiftp = false;
bool rshiftp = false;
uint16_t lshift_timer = 0;
uint16_t rshift_timer = 0;

// Number of items that are saved in prev_kcs
uint8_t prev_indx = 0;
// Used to save the last 6 actual keycodes activated by frankenkeycodes
uint16_t prev_kcs[6] = {0, 0, 0, 0, 0, 0};

// If true the deadkey characters grave and circonflexe are not automatically escaped
bool esct = false;

/*
Used to add a keycode to a prev_kcs to remember it.
When full the last code gets discarded and replaced by
the new one.
*/
void add_to_prev(uint16_t kc) {
    for (int i = 0; i < prev_indx; i++) {
        if (kc == prev_kcs[i]) return;
    }
    if (prev_indx == 6) {
        for (int i = 5; i > 0; i--) {
            prev_kcs[i] = prev_kcs[i - 1];
        }
        prev_kcs[0] = kc;
    } else {
        prev_kcs[prev_indx] = kc;
        prev_indx++;
    }
}

/*
Unregisters all codes saved in prev_kcs and resets prev_indx.
gets called on multiple occasions mainly when shift is released
and when frankenkeycodes are pressed. Prevents output of
wrong characters when really specific key combinations
that would never occur during normal usage are pressed.
*/
void unreg_prev(void) {
    if (prev_indx == 0) return;
    for (int i = 0; i < prev_indx; i++) {
        unregister_code(prev_kcs[i]);
    }
    prev_indx = 0;
}

#endif

// Interrupt and times for Nav/Esc
bool navesc = false;
uint16_t navesc_timer = 0;

// If true Gui keys and Space Cadet Shift get disabled
bool game = false;

// Interrupts all timers
void timer_timeout(void) {
    navesc = false;
    timer_timeout_keymap();
}

__attribute__((weak))
void timer_timeout_keymap(void){
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case CU_GAME:
        if(record->event.pressed) {
        timer_timeout();
        game = !game;
        }
        // allows keymap to execute further commands when CU_GAME is pressed, for example enabling a macro layer
        return process_record_keymap(keycode, record) && false; 
    case KC_LGUI:
    case KC_RGUI:
        if (record->event.pressed)
            timer_timeout();
        if (game)
            return false;
        else
            return true;
    case CU_NAV:
        if (record->event.pressed) {
            navesc       = true;
            navesc_timer = timer_read();
            //layer_on(_NAV);
        } else {
            if (timer_elapsed(navesc_timer) < TAPPING_TERM && navesc) {
                register_code(KC_ESC);
                unregister_code(KC_ESC);
            }
            //layer_off(_NAV);
        }
        return false;

#ifdef NEO2_ENABLE

    case CU_LSFT:
         if(record->event.pressed) {
      lshiftp = true;
      lshift_timer = timer_read();
      unregister_code(KC_LSFT);
      register_code(KC_LSFT);
      lshift = true;
    } else {
      unreg_prev();
      if (!rshift)
        unregister_code(KC_LSFT);
      lshift = false;
    }
        return false;

    case CU_RSFT:
        if (record->event.pressed) {
            rshiftp      = true;
            rshift_timer = timer_read();
            unregister_code(KC_LSFT);
            register_code(KC_LSFT);
            rshift = true;
        } else {
            unreg_prev();
            if (!lshift) unregister_code(KC_LSFT);
            rshift = false;
        }
        return false;



    case NEO_1_1:
        SHIFT_NORM(DE_1, DE_CIRC);
    return true;
    
    case NEO_1_2:
        SHIFT_NORM(DE_2, DE_3);
    return true;

    case NEO_1_3:
        SHIFT_NORM(DE_3, DE_3);
    return true;

    case NEO_1_4:
        SHIFT_NORM(DE_4, DE_4);
    return true;
    
    case NEO_1_5:
        SHIFT_NORM(DE_5, DE_5);
    return true;

    case NEO_1_6:
        SHIFT_NORM(DE_6, DE_4);
    return true;

    case NEO_1_7:
        SHIFT_NORMALGR(DE_7, DE_E);
    return true;

    case NEO_1_8:
        SHIFT_NO(DE_8, DE_8);
    return true;

    case NEO_1_9:
        SHIFT_NO(DE_9, DE_E);
    return true;

    case NEO_1_0:
        SHIFT_NO(DE_0, DE_0);
    return true;


#endif

    // Turn RGB Red when going to Bootloader
    case RESET:
      if(record->event.pressed) {
        rgb_change_color(HSV_RED);
      }
    return true;

    case MY_PASS:
      if(record->event.pressed) {
        //when pressed
        SEND_STRING("Mzpasswordisthesafest!\n");
      }
    return true;

    default:
        if (record->event.pressed) {
            timer_timeout();

#ifdef NEO2_ENABLE
            if (lshift || rshift)
                register_code(KC_LSFT);
            else
                unregister_code(KC_LSFT);
#endif
        }
        return process_record_keymap(keycode, record);
  }
}

__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void rgb_change_color(uint8_t hue, uint8_t sat, uint8_t val) {
    rgblight_sethsv_eeprom_helper(hue, sat, val, 1);
    rgblight_set(); // Utility functions do not call rgblight_set() automatically, so they need to be called explicitly.
}
