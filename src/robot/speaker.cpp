#include "speaker.h"

Speaker::Speaker() {
    pinMode(pin, OUTPUT);
}

void Speaker::play(int toneFreq, int duration) {
    tone(pin, toneFreq, duration);
}
