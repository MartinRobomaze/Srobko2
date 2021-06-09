// Pridanie kniznic srobka.
#include <Arduino.h>
#include <robot/types.h>
#include <robot/motors.h>

Motors motors;
ArmPosition position;

// Program zbehne raz.
void setup() {
    
}

// Program sa opakuje.
void loop() {
    // Nastavenie vertikalnej pozicie lavej ruky na 90 stupnov.
    position.armY = 90;
    motors.moveLeftArm(position);
    // Cakaj 1 sekundu.
    delay(1000);

    // Nastavenie vertikalnej pozicie lavej ruky na 0 stupnov.
    position.armY = 0;
    motors.moveLeftArm(position);
    // Cakaj 1 sekundu.
    delay(1000);
}
