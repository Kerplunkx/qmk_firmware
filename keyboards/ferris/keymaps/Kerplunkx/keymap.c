#include QMK_KEYBOARD_H
#include "oneshot.h"

#define HOME G(KC_LEFT)
#define END G(KC_RGHT)
#define FWD G(KC_RBRC)
#define BACK G(KC_LBRC)
#define TABL G(S(KC_LBRC))
#define TABR G(S(KC_RBRC))
#define SPCL A(G(KC_LEFT))
#define SPC_R A(G(KC_RGHT))
#define LA_SYM MO(SYM)
#define LA_NAV MO(NAV)
#define LA_NUM MO(NUM)

enum keycodes {
	OS_RSHFT = SAFE_RANGE,
	OS_LSHTF,
	OS_CTRL,
	OS_ALT,
	OS_GUI,
};

enum layers {
    STRDY = 0,
    NAV,
    SYM,
    NUM,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[STRDY] = LAYOUT(
        KC_V, KC_M, KC_L, KC_C, KC_P,    KC_X, KC_F, KC_O,    KC_U,   KC_J,
        KC_S, KC_T, KC_R, KC_D, KC_Y,    QK_REP, KC_N, KC_A,    KC_E,   KC_I,
        KC_Z, KC_K, KC_Q, KC_G, KC_W,    KC_B, KC_H, KC_COMM, KC_DOT, KC_SLSH,
	                        LA_NAV,KC_SPC, MO(NUM), LA_SYM
	),
  [NAV] = LAYOUT(
        KC_TAB,  XXXXXXX,  TABL,    TABR,    KC_VOLU, QK_BOOT, HOME,    KC_UP,   END,     KC_DEL,
        OS_LSHTF, OS_CTRL, OS_ALT,  OS_GUI,  KC_VOLD, KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,
        SPCL,    SPC_R,   BACK,    FWD,     KC_MPLY, XXXXXXX, KC_PGDN, KC_PGUP, XXXXXXX, KC_ENT,
                                   _______, _______, _______, _______
	),
  [SYM] = LAYOUT(
		    KC_ESC,  KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD, KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_QUOT,
		    KC_MINS, KC_ASTR, KC_EQL,  KC_UNDS, KC_DLR,  KC_HASH, OS_GUI,  OS_ALT,  OS_CTRL, OS_RSHFT,
		    KC_PLUS, KC_PIPE, KC_AT,   KC_BSLS, KC_PERC, KC_GRV, KC_AMPR, KC_SCLN, KC_COLN, KC_EXLM,
		                               _______, _______, _______, _______
	),
  [NUM] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        OS_LSHTF, OS_CTRL, OS_ALT,  OS_GUI,  KC_F11,  KC_F10,  OS_GUI,  OS_ALT,  OS_CTRL, OS_RSHFT,
        KC_F7,   KC_F5,   KC_F3,   KC_F1,   KC_F9,   KC_F8,   KC_F12,  KC_F2,   KC_F4,   KC_F6,
                                   _______, _______, _______, _______
	),
};
// clang-format on


bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case KC_LSFT:
    case OS_LSHTF:
    case OS_RSHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_GUI:
        return true;
    default:
        return false;
    }
}

oneshot_state os_lshft_state = os_up_unqueued;
oneshot_state os_rshft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_gui_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_oneshot(
        &os_lshft_state, KC_LSFT, OS_LSHTF,
        keycode, record
    );
    update_oneshot(
        &os_rshft_state, KC_RSFT, OS_RSHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_gui_state, KC_LGUI, OS_GUI,
        keycode, record
    );

    return true;
}

// layer_state_t layer_state_set_user(layer_state_t state) {
//     return update_tri_layer_state(state, SYM, NAV, NUM);
// }
