#include <Arduino.h>

#ifndef BUTTON_H
#define BUTTON_H

class Button {
    public:
        /**
         * @brief Construct a new Button object
         * 
         * @param _buttonIndex
         */
        Button(uint8_t _buttonIndex);
        
        /**
         * @brief Reads the current state of button.
         * 
         */
        bool isPressed();
    private:
        uint8_t buttonIndex;
        uint8_t buttonPins[6] = {35, 36, 37, 38, 39, 40};

        bool previousState = 0;
};

#endif
