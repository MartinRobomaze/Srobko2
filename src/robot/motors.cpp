#include <Arduino.h>
#include "motors.h"

Motors::Motors() {
    for (int i = 0; i < 25; i++) {
        servos[i].attach(servoPins[i]);
        servos[i].write(initValues[i]);
        servoAngles[i] = initValues[i];
    }
}

void Motors::moveLeftHand(int armX, int armY, int armRot, int elbow, int handRot, int hand) {
    armY = map(armY, 0, 180, 180, 0);
    armRot = map(armRot, 0, 180, 180, 0);
    elbow = map(elbow, 0, 115, 160, 50);
    handRot = map(handRot, 0, 140, 140, 0);
    hand = map(hand, 0, 60, 160, 100);

    servos[1].write(armY);
    servos[3].write(armX);
    servos[5].write(armRot);

    servos[7].write(elbow);

    servos[11].write(handRot);
    servos[13].write(hand);
}

void Motors::moveRightHand(int armX, int armY, int armRot, int elbow, int handRot, int hand) {
    armRot = map(armRot, 0, 90, 170, 80);
    elbow = map(elbow, 0, 115, 5, 110);
    hand = map(hand, 0, 60, 10, 60);

    servos[0].write(armY);
    servos[2].write(armX);
    servos[4].write(armRot);

    servos[6].write(elbow);

    servos[10].write(handRot);
    servos[12].write(hand);
}

void Motors::writeMotor(int motorIndex, int value) {
    if (motorIndex > 25) {
        return;
    }

    if (value < 0 || value > 180) {
        return;
    }

    servos[motorIndex].write(value);
    servoAngles[motorIndex] = value;
}

int Motors::getMotor(int motorIndex) {
    if (motorIndex > 25) {
        return -1;
    }

    return servoAngles[motorIndex];
}
