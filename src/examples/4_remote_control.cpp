#include <Arduino.h>
#include <robot/radio.h>
#include <robot/motors.h>
#include <robot/types.h>

Radio radio;
Motors motors;

void setup() {

}

void loop() {
    RobotPosition position;

    // Precitaj data z ovladaca.
    bool newData = radio.readData(position);

    // Ak si dostal nove data.
    if (newData) {
        // Nastav motory na prijatu poziciu.
        motors.move(position);
    }
}
