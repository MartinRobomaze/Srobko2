#ifndef TYPES_H
#define TYPES_H

/**
 * @brief Holds the position of an arm.
 * 
 */
struct ArmPosition {
    int armX;
    int armY;
    int armRot;
    int elbow;
    int handRot;
    int handAngle;

    /**
     * @brief Construct a new Arm Position object.
     * 
     */
    ArmPosition(): armX(0), armY(0), armRot(0), elbow(0), handRot(0), handAngle(0) {}
};

/**
 * @brief Holds the position of head.
 * 
 */
struct HeadPosition {
    int headX;
    int headY;

    /**
     * @brief Construct a new Head Position object.
     * 
     */
    HeadPosition(): headX(0), headY(0) {}
};

/**
 * @brief Holds the position of the robot.
 * 
 */
struct RobotPosition {
    HeadPosition head;
    ArmPosition leftArm;
    ArmPosition rightArm;

    /**
     * @brief Construct a new Robot Position object.
     * 
     */
    RobotPosition(): head(HeadPosition()), leftArm(ArmPosition()), rightArm(ArmPosition()) {}

    /**
     * @brief Parses raw data to RobotPosition.
     * 
     * @param position 
     * @param data 
     */
    void parseRawData(uint8_t data[25]) {
        leftArm.armY = data[1];
        leftArm.armX = data[3];
        leftArm.armRot = data[5];

        leftArm.elbow = data[7];

        leftArm.handRot = data[11];
        leftArm.handAngle = data[13];

        rightArm.armY = data[0];
        rightArm.armX = data[2];
        rightArm.armRot = data[4];

        rightArm.elbow = data[6];

        rightArm.handRot = data[10];
        rightArm.handAngle = data[12];

        head.headY = data[8];
        head.headX = data[9];
    }

    /**
     * @brief Parses RobotPosition to raw data.
     * 
     * @param data 
     */
    void toRawData(char data[25]) {
        data[1] = leftArm.armY;
        data[3] = leftArm.armX;
        data[5] = leftArm.armRot;

        data[7] = leftArm.elbow;

        data[11] = leftArm.handRot;
        data[13] = leftArm.handAngle;

        data[0] = rightArm.armY;
        data[2] = rightArm.armX;
        data[4] = rightArm.armRot;

        data[6] = rightArm.elbow;

        data[10] = rightArm.handRot;
        data[12] = rightArm.handAngle;

        data[8] = head.headY;
        data[9] = head.headX;
    }
};
#endif
