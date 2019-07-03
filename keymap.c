#include QMK_KEYBOARD_H
#define _STANDARD 0
#define _SELECT 1
#define _ARROW 2
#define _NUMPAD 3
#define _JAPANESE 4
#define _COLOR 5

uint8_t prev = _STANDARD;

enum custom_keycodes
{
    STANDARD = SAFE_RANGE,
    NUMPAD,
    JAPANESE,
    COLOR
};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode)
    {
        case STANDARD:
            if (record->event.pressed)
            {
                // Changes layer to standard and language to English when
                // spacebar is held and FN is pressed.
                SEND_STRING(SS_TAP(X_LANG1));
                layer_invert(_STANDARD);
            }
            break;

        case NUMPAD:
            if (record->event.pressed)
            {
                // Changes layer to numpad and lanaguage to English when
                // spacebar is held and Menu key is pressed.
                SEND_STRING(SS_TAP(X_LANG1));
                layer_invert(_NUMPAD);
            }
            break;

        case JAPANESE:
            if (record->event.pressed)
            {
                // Changes layer to Japanese and language to Japanese when
                // spacebar is held and Alt key is pressed.
                SEND_STRING(SS_TAP(X_INT2));
                layer_invert(_JAPANESE);
            }
            break;

        case COLOR:
            if (record->event.pressed)
            {
                // Changes layer to color and language to English when
                // spacebar is held and Ctrl key is pressed.
                SEND_STRING(SS_TAP(X_LANG1));
                layer_invert(_COLOR);
            }
            break;
    }
    return true;
};

uint32_t layer_state_set_user(uint32_t state)
{
    uint8_t layer = biton32(state);

    if (prev != layer)
    {
        switch (layer)
        {
            // Standard layer is solid orange color.
            case _STANDARD:
                rgblight_sethsv_orange();
                rgblight_mode(1);
                break;

            // When waiting for user to select new layer, changes RGB to circular mode.
            case _SELECT:
                rgblight_mode(15);
                break;

            // When in arrow key layer, softly strobe light.
            case _ARROW:
                rgblight_mode(3);
                break;

            // Numpad layer is solid green color.
            case _NUMPAD:
                rgblight_sethsv_green();
                rgblight_mode(1);
                break;

            // Japanese layer is solid red color.
            case _JAPANESE:
                rgblight_sethsv_red();
                rgblight_mode(1);
                break;

            // Color select layer is rainbow color mode.
            case _COLOR:
                rgblight_mode(6);
                break;
        }
    }
    prev = layer;

    return state;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{
    // Standard QWERTY. Holding CAPS LOCK or FN triggers layer 2 (arrow),
    // Holding spacebar triggers layer 1 (select), and pressing a key to the right while holding spacebar
    // can select layers 3-5.
	[0] = LAYOUT_60_ansi(
        KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        MO(_ARROW), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, LT(_SELECT, KC_SPC), MO(_ARROW), KC_APP, KC_RALT, KC_RCTL),

    // While spacebar is held, pressing FN selects layer 0 (standard), pressing Menu key selects layer 3 (numpad),
    // pressing alt key selects layer 4 (Japanese), pressing ctrl key selects layer 5 (color)
    [1] = LAYOUT_60_ansi(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, LT(_SELECT, KC_SPC), STANDARD, NUMPAD, JAPANESE, COLOR),

    // Layer with arrow keys and function keys. Access by holding CAPS LOCK or FN while in standard layer.
	[2] = LAYOUT_60_ansi(
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
        KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_MPLY,
        KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, LT(_SELECT, KC_SPC), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    // Layer with numpad and function keys. Hold spacebar to select different layer.
	[3] = LAYOUT_60_ansi(
        KC_NLCK, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS,
        KC_PSLS, KC_P7, KC_P8, KC_P9, KC_PMNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_PAST, KC_P4, KC_P5, KC_P6, KC_PPLS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_PENT, KC_P1, KC_P2, KC_P3, KC_PEQL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_PCMM, KC_PDOT, KC_P0, LT(_SELECT, KC_SPC), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    // Layer with Japanese input (same as standard layer but with Kana input). Hold spacebar to select different layer.
	[4] = LAYOUT_60_ansi(
        KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        MO(_ARROW), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, LT(_SELECT, KC_SPC), MO(_ARROW), KC_APP, KC_RALT, KC_RCTL),

    // Layer with color adjustment. Hold spacebar to select different layer.
	[5] = LAYOUT_60_ansi(
        RGB_TOG, RGB_MOD, RGB_RMOD, RGB_SPI, RGB_SPD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, RGB_HUI, RGB_HUD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, RGB_SAI, RGB_SAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, LT(_FN, KC_SPC), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)

};
