// Pridanie kniznic srobka.
#include <Arduino.h>
#include <robot/types.h>
#include <robot/motors.h>
#include <robot/button.h>

headPosition position;
Motors motors;

Button b1(0);
Button b2(1);

// Program zbehne raz.
void setup() {
    Serial.begin(9600);
}

// Program sa opakuje.
void loop() {
    if (b1.isPressed()) {
        Serial.println("tlacidlo 1 je stlacene");

        position.headX = 90;
        motors.moveHead(position);
    } else if (b2.isPressed()) {
        Serial.println("tlacidlo 2 je stlacene");

        position.headX = -90;
        motors.moveHead(position);
    } else {
        
    }
}
