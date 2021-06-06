#include <Arduino.h>
#include "motors.h"


Motors::Motors() {
    for (int i = 0; i < 25; i++) {
        servos[i].attach(motorsPins[i]);
        servos[i].write(initValues[i]);
    }
}

Motors::Motors(uint8_t _motorsPins[25]) {
    for (int i = 0; i < 25; i++) {
        servos[i].attach(_motorsPins[i]);
        servos[i].write(initValues[i]);
        motorsPins[i] = _motorsPins[i];
    }
}

void Motors::move(RobotPosition position) {
    moveLeftArm(position.leftArm);
    moveRightArm(position.rightArm);
    moveHead(position.head);
}

void Motors::moveLeftArm(ArmPosition position) {
    servos[1].write(position.armY);
    servos[3].write(position.armX);
    servos[5].write(position.armRot);

    servos[7].write(position.elbow);

    servos[11].write(position.handRot);
    servos[13].write(position.handAngle);
}

void Motors::moveRightArm(ArmPosition position) {
    servos[0].write(position.armY);
    servos[2].write(position.armX);
    servos[4].write(position.armRot);

    servos[6].write(position.elbow);

    servos[10].write(position.handRot);
    servos[12].write(position.handAngle);
}

void Motors::moveHead(HeadPosition position) {
    servos[8].write(position.headY);
    servos[9].write(position.headX);
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
}
