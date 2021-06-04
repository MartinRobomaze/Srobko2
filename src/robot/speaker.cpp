#include "speaker.h"

Speaker::Speaker(uint8_t _pin) {
    pin = _pin;

    pinMode(pin, OUTPUT);
}

void Speaker::play(int toneFreq, int duration) {
    tone(pin, toneFreq, duration);
}
