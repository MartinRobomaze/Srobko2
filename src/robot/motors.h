#include <Servo.h>

#ifndef MOTORS
#define MOTORS

class Motors {
    public:
        Motors();
        void moveRightHand(int armX, int armY, int armRot, int elbow, int handRot, int hand);
        void moveLeftHand(int armX, int armY, int armRot, int elbow, int handRot, int hand);

        void moveHead(int headX, int headY);

        int getMotor(int motorIndex);
        void writeMotor(int motorIndex, int value);
    private:
        Servo servos[25];
        int servoAngles[25];

        int servoPins[25] = {9, 17, 12, 20, 13, 21, 10, 18, 31, 30, 11, 45, 8, 16, 4, 3, 33, 32, 5, 2, 7, 15, 6, 14, 34};
        int initValues[25] = {0, 180, 170, 0, 90, 90, 5, 160, 90, 40, 0, 140, 10, 160, 95, 100, 60, 90, 0, 0, 55, 35, 160, 5, 90};
};

#endif
