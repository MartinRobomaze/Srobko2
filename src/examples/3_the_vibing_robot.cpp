// Kniznice pre srobka.
#include <Arduino.h>
#include <robot/speaker.h>
#include <robot/types.h>
#include <robot/motors.h>
#include <robot/tones.h>

// Noty "Ievann Polkky".
int tones[] = {AS3, AS3, DS4, DS4, F4, FS4, DS4, DS4, FS4, F4, CS4, CS4, F4, FS4, DS4, DS4, AS3, AS3, DS4, DS4, F4, FS4, DS4, DS4, FS4, AS4, GS4, FS4, F4, FS4, DS4, DS4};
int bpm = 130;

// Pozicia hlava hore.
HeadPosition headUp;
// Pozicia hlava dole.
HeadPosition headDown;
Motors motors;
Speaker speaker;

void setup() {
    // Nastavenie pozicii hlava hore a hlava dole.
    headUp.headY = 90;
    headDown.headY = 0;
}

void loop() {
    // Opakuj 32 krat.
    for (int i = 0; i < 32; i++) {
        // Dlzka tonu - 1 sekunda / 8 * takt.
        int toneDuration = 1000 / (bpm * 8);
        // Hraj notu.
        speaker.play(tones[i], toneDuration);

        // Ak je i nasobok 8.
        if (i % 8 == 0) {
            // Pohni hlavu hore.
            motors.moveHead(headUp);
        } 
        // Ak je i nasobok 4.
        else if (i % 4 == 0) {
            // Pohni hlavu dole.
            motors.moveHead(headDown);
        }

        delay(toneDuration);
    }
}
