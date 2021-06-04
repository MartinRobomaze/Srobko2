#include "button.h"

Button::Button(uint8_t _buttonIndex) {
    buttonIndex = _buttonIndex;

    pinMode(buttonIndex, INPUT_PULLUP);
}

void Button::setCallback(buttonPressedCallback _callback) {
    callback = _callback;
}

void Button::update() {
    bool buttonState = digitalRead(buttonPins[buttonIndex]);

    if (buttonState && buttonState != previousState) {
        callback();
    }

    previousState = buttonState;
}
