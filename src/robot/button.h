#include <Arduino.h>

#ifndef BUTTON_H
#define BUTTON_H

typedef void (*buttonPressedCallback)();

class Button {
    public:
        Button(uint8_t _pin, buttonPressedCallback _callback);
        void update();
    private:
        uint8_t pin;
        buttonPressedCallback callback;
};

#endif