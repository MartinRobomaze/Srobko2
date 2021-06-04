#include <Arduino.h>
#include "motors.h"

Motors::Motors() {
    for (int i = 0; i < 25; i++) {
        servos[i].attach(servoPins[i]);
        servos[i].write(initValues[i]);
        servoAngles[i] = initValues[i];
    }
}

void Motors::moveLeftHand(int armX, int armY, int armRot, int elbow, int handRot, int handAngle) {
    servos[1].write(armY);
    servos[3].write(armX);
    servos[5].write(armRot);

    servos[7].write(elbow);

    servos[11].write(handRot);
    servos[13].write(handAngle);

    servoAngles[1] = armY;
    servoAngles[3] = armX;
    servoAngles[5] = armRot;

    servoAngles[7] = elbow;

    servoAngles[11] = handRot;
    servoAngles[13] = handAngle;
}

void Motors::moveRightHand(int armX, int armY, int armRot, int elbow, int handRot, int handAngle) {
    servos[0].write(armY);
    servos[2].write(armX);
    servos[4].write(armRot);

    servos[6].write(elbow);

    servos[10].write(handRot);
    servos[12].write(handAngle);

    servoAngles[0] = armY;
    servoAngles[2] = armX;
    servoAngles[4] = armRot;

    servoAngles[6] = elbow;

    servoAngles[10] = handRot;
    servoAngles[12] = handAngle;
}

void Motors::writeMotor(int motorIndex, int value) {
    if (motorIndex > 25) {
        return;
    }

    if (value < 0 || value > 180) {
        return;
    }

    value = map(value, 0, 180, servoMinValues[motorIndex], servoMaxValues[motorIndex]);

    servos[motorIndex].write(value);
    servoAngles[motorIndex] = value;
}

int Motors::getMotor(int motorIndex) {
    if (motorIndex > 25) {
        return -1;
    }

    return servoAngles[motorIndex];
}
