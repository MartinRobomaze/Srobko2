#include <Arduino.h>

#ifndef SPEAKER_H
#define SPEAKER_H

class Speaker {
    public:
        /**
         * @brief Construct a new Speaker object
         * 
         * @param pin 
         */
        Speaker(uint8_t _pin);
        
        /**
         * @brief Plays a tone for a specified amount of time.
         * 
         * @param toneFreq 
         * @param duration 
         */
        void play(int toneFreq, int duration);
    private:
        uint8_t pin;
};

#endif