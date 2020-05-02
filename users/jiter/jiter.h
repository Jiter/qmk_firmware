#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"
#include "keymap_extras/keymap_german.h"
#include "rgblight.h"

void rgb_change_color(uint8_t hue, uint8_t sat, uint8_t val);

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes { 
MY_PASS = SAFE_RANGE, 

CU_LSFT,
CU_RSFT,

CU_GAME, 
CU_NAV,

NEO_1_1,
NEO_1_2,
NEO_1_3,
NEO_1_4,
NEO_1_5,
NEO_1_6,
NEO_1_7,
NEO_1_8,
NEO_1_9,
NEO_1_0,

};

#ifdef NEO2_ENABLE

extern bool     lshift;
extern bool     rshift;

extern uint8_t  prev_indx;
extern uint16_t prev_kcs[6];
void            add_to_prev(uint16_t kc);
void            unreg_prev(void);

extern bool esct;
#endif

extern bool     navesc;
extern uint16_t navesc_timer;

extern bool game;

void timer_timeout(void);

void timer_timeout_keymap(void);

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

#define CTRLX LCTL(KC_X)
#define CTRLC LCTL(KC_C)
#define CTRLV LCTL(KC_V)

#define ALTF4 LALT(KC_F4)

#define GUIU LGUI(KC_UP)
#define GUID LGUI(KC_DOWN)
#define GUIL LGUI(KC_LEFT)
#define GUIR RGUI(KC_RIGHT)

#define CTLENT CTL_T(KC_ENT)

#define EMOJI LWIN(KC_DOT)

/*
Templates for Keys, with custom shifted and non shifted Characters
*/

// Normal shift status
#define SHIFT_NORM(kc1, kc2)          \
    if (record->event.pressed) {      \
        timer_timeout();              \
        if (lshift || rshift) {       \
            register_code(KC_LSFT);   \
            unregister_code(kc2);     \
            register_code(kc2);       \
            add_to_prev(kc2);         \
        } else {                      \
            unregister_code(KC_LSFT); \
            unregister_code(kc1);     \
            register_code(kc1);       \
        }                             \
    } else {                          \
        unregister_code(kc1);         \
        unregister_code(kc2);         \
    }                                 \
    return false;

// Inverted shift status
#define SHIFT_SWITCH(kc1, kc2)        \
    if (record->event.pressed) {      \
        timer_timeout();              \
        if (lshift || rshift) {       \
            unregister_code(KC_LSFT); \
            unregister_code(kc2);     \
            register_code(kc2);       \
            add_to_prev(kc2);         \
        } else {                      \
            register_code(KC_LSFT);   \
            unregister_code(kc1);     \
            register_code(kc1);       \
            add_to_prev(kc1);         \
        }                             \
    } else {                          \
        unregister_code(kc1);         \
        unregister_code(kc2);         \
        unreg_prev();                 \
        if (lshift || rshift)         \
            register_code(KC_LSFT);   \
        else                          \
            unregister_code(KC_LSFT); \
    }                                 \
    return false;

// Always shifted
#define SHIFT_ALL(kc1, kc2)           \
    if (record->event.pressed) {      \
        timer_timeout();              \
        register_code(KC_LSFT);       \
        if (lshift || rshift) {       \
            unregister_code(kc2);     \
            register_code(kc2);       \
            add_to_prev(kc2);         \
        } else {                      \
            unregister_code(kc1);     \
            register_code(kc1);       \
            add_to_prev(kc1);         \
        }                             \
    } else {                          \
        unregister_code(kc1);         \
        unregister_code(kc2);         \
        unreg_prev();                 \
        if (lshift || rshift)         \
            register_code(KC_LSFT);   \
        else                          \
            unregister_code(KC_LSFT); \
    }                                 \
    return false;

// Never shifted
#define SHIFT_NO(kc1, kc2)            \
    if (record->event.pressed) {      \
        timer_timeout();              \
        unregister_code(KC_LSFT);     \
        if (lshift || rshift) {       \
            unregister_code(kc2);     \
            register_code(kc2);       \
            add_to_prev(kc2);         \
        } else {                      \
            unregister_code(kc1);     \
            register_code(kc1);       \
        }                             \
    } else {                          \
        unregister_code(kc1);         \
        unregister_code(kc2);         \
        unreg_prev();                 \
        if (lshift || rshift)         \
            register_code(KC_LSFT);   \
        else                          \
            unregister_code(KC_LSFT); \
    }                                 \
    return false;

// Always AltGr
#define SHIFT_ALGR(kc1, kc2)        \
    if (record->event.pressed) {    \
        timer_timeout();            \
        unregister_code(KC_LSFT);   \
        register_code(KC_ALGR);     \
        if (lshift || rshift) {     \
            unregister_code(kc2);   \
            register_code(kc2);     \
            unregister_code(kc2);   \
            register_code(KC_LSFT); \
        } else {                    \
            unregister_code(kc1);   \
            register_code(kc1);     \
            unregister_code(kc1);   \
        }                           \
        unregister_code(KC_ALGR);   \
    }                               \
    return false;

// Inverted shift status
#define SHIFT_NORMALGR(kc1, kc2)      \
    if (record->event.pressed) {      \
        timer_timeout();              \
        if (lshift || rshift) {       \
            register_code(KC_ALGR);   \
            unregister_code(KC_LSFT); \
            unregister_code(kc2);     \
            register_code(kc2);       \
            add_to_prev(kc2);         \
        } else {                      \
            unregister_code(KC_LSFT); \
            unregister_code(kc1);     \
            register_code(kc1);       \
        }                             \
    } else {                          \
        unregister_code(kc1);         \
        unregister_code(kc2);         \
        unregister_code(KC_ALGR);     \
    }                                 \
    return false;

// Different keycode when Ctrl is pressed
#define CTRL(kc1, kc2)                                                       \
    if (record->event.pressed) {                                             \
        timer_timeout();                                                     \
        if (lshift || rshift)                                                \
            register_code(KC_LSFT);                                          \
        else                                                                 \
            unregister_code(KC_LSFT);                                        \
        if (keyboard_report->mods & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL))) { \
            register_code(kc2);                                              \
        } else {                                                             \
            register_code(kc1);                                              \
        }                                                                    \
    } else {                                                                 \
        unregister_code(kc1);                                                \
        unregister_code(kc2);                                                \
    }                                                                        \
    return false;

// Template for keys on deadkey layer (mostly Umlaute)
#define UML(kc)                       \
    if (record->event.pressed) {      \
        timer_timeout();              \
        if (lshift || rshift)         \
            register_code(KC_LSFT);   \
        else                          \
            unregister_code(KC_LSFT); \
        register_code(kc);            \
        unregister_code(kc);          \
        layer_off(_DEADKEY);          \
    }                                 \
    return false;

#endif