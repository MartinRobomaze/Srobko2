#include <Arduino.h>

#ifndef BUTTON_H
#define BUTTON_H

typedef void (*buttonPressedCallback)();

class Button {
    public:
        /**
         * @brief Construct a new Button object
         * 
         * @param _buttonIndex
         */
        Button(uint8_t _buttonIndex);

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
        uint8_t buttonIndex;
        uint8_t buttonPins[6] = {35, 36, 37, 38, 39, 40};
        buttonPressedCallback callback;

        bool previousState = 0;
};

#endif