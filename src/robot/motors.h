#include <Servo.h>

#ifndef MOTORS
#define MOTORS

class Motors {
    public:
        /**
         * @brief Construct a new Motors object
         */
        Motors();

        /**
         * @brief Moves the right hand of the robot.
         * 
         * @param armX 
         * @param armY 
         * @param armRot 
         * @param elbow 
         * @param handRot 
         * @param handAngle 
         */
        void moveRightHand(int armX, int armY, int armRot, int elbow, int handRot, int handAngle);
        /**
         * @brief Moves the left hand of the robot.
         * 
         * @param armX 
         * @param armY 
         * @param armRot 
         * @param elbow 
         * @param handRot 
         * @param handAngle 
         */
        void moveLeftHand(int armX, int armY, int armRot, int elbow, int handRot, int handAngle);

        /**
         * @brief Moves the head of the robot.
         * 
         * @param headX 
         * @param headY 
         */
        void moveHead(int headX, int headY);

        /**
         * @brief Gets the angle of motor.
         * 
         * @param motorIndex 
         * @return int 
         */
        int getMotor(int motorIndex);
        /**
         * @brief Writes specified angle to the motor.
         * 
         * @param motorIndex 
         * @param value 
         */
        void writeMotor(int motorIndex, int value);
    private:
        Servo servos[25];
        int servoAngles[25];

        int servoPins[25] = {9, 17, 12, 20, 13, 21, 10, 18, 31, 30, 11, 45, 8, 16, 4, 3, 33, 32, 5, 2, 7, 15, 6, 14, 34};
        int initValues[25] = {0, 180, 170, 0, 90, 90, 5, 160, 90, 40, 0, 140, 10, 160, 95, 100, 60, 90, 0, 0, 55, 35, 160, 5, 90};

        int servoMinValues[25] = {0, 180, 170, 0, 0, 180, 5, 160, 110, 0, 0, 140, 10, 160, 145, 145, 40, 70, 0, 0, 30, 10, 160, 5, 70};
        int servoMaxValues[25] = {180, 0, 80, 90, 180, 0, 110, 50, 60, 90, 140, 0, 60, 100, 0, 0, 110, 115, 110, 110, 180, 160, 130, 60, 110};
};

#endif
