#include "button.h"

Button::Button(uint8_t _buttonIndex) {
    buttonIndex = _buttonIndex;

    pinMode(buttonIndex, INPUT_PULLUP);
}

bool Button::isPressed() {
    return !digitalRead(buttonPins[buttonIndex]);
}