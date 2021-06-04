#include "button.h"

Button::Button(uint8_t _pin) {
    pin = _pin;

    pinMode(pin, INPUT_PULLUP);
}

void Button::setCallback(buttonPressedCallback _callback) {
    callback = _callback;
}

void Button::update() {
    if (digitalRead(pin)) {
        callback();
    }
}
