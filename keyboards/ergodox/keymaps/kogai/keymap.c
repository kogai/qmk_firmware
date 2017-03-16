#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_fr_ch.h"
#include "keymap_french.h"
#include "keymap_german.h"
#include "keymap_german_ch.h"
#include "keymap_nordic.h"
#include "keymap_norwegian.h"
#include "keymap_spanish.h"

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = KEYMAP(
    KC_ESCAPE,      KC_1,         KC_2,         KC_3,         KC_4,   KC_5,    KC_RIGHT,
    KC_TAB,         KC_Q,         KC_W,         KC_E,         KC_R,   KC_T,    TG(1),
    KC_EQL,         KC_A,         KC_S,         KC_D,         KC_F,   KC_G,
    KC_LSHIFT,      CTL_T(KC_Z),  KC_X,         KC_C,         KC_V,   KC_B,    KC_RIGHT,
    KC_LCTL,        KC_LALT,      KC_LBRACKET,  KC_RBRACKET,  KC_GRAVE,

                KC_QUOTE,   KC_GRAVE,
                            KC_LEFT,
    KC_LGUI,    KC_SPACE,   LT(1, KC_LANG2),

    KC_LEFT,      KC_6,         KC_7,       KC_8,     KC_9,     KC_0,             M(1),
    TG(2),        KC_Y,         KC_U,       KC_I,     KC_O,     KC_P,             M(2),
                  KC_H,         KC_J,       KC_K,     KC_L,     LT(2,KC_SCOLON),  KC_MINUS,
    KC_LEFT,      KC_N,         KC_M,       KC_COMMA, KC_DOT,   CTL_T(KC_SLASH),  KC_RSHIFT,
                                KC_LEFT,    KC_UP,    KC_DOWN,  KC_RIGHT,         KC_CAPS,

    KC_MINUS,   KC_BSLS,
    KC_RIGHT,
    LT(1, KC_LANG1),   KC_BSPACE,        KC_ENTER
  ),

  [1] = KEYMAP(
    M(0),   KC_F1,    KC_F2,  KC_F3,    KC_F4,    KC_F5,    KC_TRANSPARENT,
    RESET,  KC_EXLM,  KC_AT,  KC_LCBR,  KC_RCBR,  KC_PIPE,  KC_TRANSPARENT,
    KC_TRANSPARENT,KC_HASH,KC_DLR,KC_LPRN,KC_RPRN,KC_GRAVE,
    KC_TRANSPARENT,KC_PERC,KC_CIRC,KC_LBRACKET,KC_RBRACKET,KC_TILD,KC_TRANSPARENT,
    KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_WH_DOWN,KC_MS_WH_UP,

    RGB_MOD,            KC_TRANSPARENT,
                        KC_TRANSPARENT,
    RGB_VAD,  RGB_VAI,  KC_TRANSPARENT,

    KC_TRANSPARENT,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,
    KC_TRANSPARENT,KC_UP,KC_7,KC_MS_U,KC_9,KC_ASTR,KC_F12,
    KC_DOWN,KC_MS_L,KC_MS_D,KC_MS_R,KC_PLUS,KC_MEDIA_EJECT,
    KC_TRANSPARENT,KC_AMPR,KC_1,KC_2,KC_3,KC_BSLASH,KC_TRANSPARENT,
    KC_BTN1,KC_BTN2,KC_BTN3,KC_BTN4,KC_BTN5,

    RGB_TOG,RGB_SLD,
    KC_MUTE,
    KC_TRANSPARENT, KC_VOLD, KC_VOLU
  ),

  [2] = KEYMAP(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_UP,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_BTN1,KC_MS_BTN2,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MEDIA_PLAY_PAUSE,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_TRANSPARENT,KC_TRANSPARENT,KC_AUDIO_VOL_UP,KC_AUDIO_VOL_DOWN,KC_AUDIO_MUTE,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_WWW_BACK),

};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        case 1:
        if (record->event.pressed) {
            return MACRO(T(LBRACKET), T(RBRACKET), END); // []
        }
        case 2:
        if (record->event.pressed) {
            return MACRO(D(LSFT), T(LBRACKET), T(RBRACKET), U(LSFT), END); // {}
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
      break;

  }
  return true;
}

void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }

};
