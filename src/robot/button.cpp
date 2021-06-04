#include "button.h"

Button::Button(uint8_t _pin, buttonPressedCallback _callback) {
    pin = _pin;
    callback = _callback;

    pinMode(pin, INPUT_PULLUP);
}

void Button::update() {
    if (digitalRead(pin)) {
        callback();
    }
}
