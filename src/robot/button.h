#include <Arduino.h>

#ifndef BUTTON_H
#define BUTTON_H

typedef void (*buttonPressedCallback)();

class Button {
    public:
        /**
         * @brief Construct a new Button object
         * 
         * @param _pin 
         */
        Button(uint8_t _pin);

        /**
         * @brief Set the callback function to be called after button press.
         * 
         */
        void setCallback(buttonPressedCallback);
        
        /**
         * @brief Updates the button state.
         * 
         */
        void update();
    private:
        uint8_t pin;
        buttonPressedCallback callback;
};

#endif