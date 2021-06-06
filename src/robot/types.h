/**
 * @brief Holds the position of an arm.
 * 
 */
struct armPosition {
    int armX;
    int armY;
    int armRot;
    int elbow;
    int handRot;
    int handAngle;
};

/**
 * @brief Holds the position of head.
 * 
 */
struct headPosition {
    int headX;
    int headY;
};

/**
 * @brief Holds the position of the robot.
 * 
 */
struct robotPosition {
    headPosition head;
    armPosition leftArm;
    armPosition rightArm;
};

/**
 * @brief Parses raw data to robotPosition.
 * 
 * @param position 
 * @param data 
 */
void parseRawData(robotPosition &position, uint8_t data[25]) {
    position.leftArm.armY = data[1];
    position.leftArm.armX = data[3];
    position.leftArm.armRot = data[5];

    position.leftArm.elbow = data[7];

    position.leftArm.handRot = data[11];
    position.leftArm.handAngle = data[13];

    position.rightArm.armY = data[0];
    position.rightArm.armX = data[2];
    position.rightArm.armRot = data[4];

    position.rightArm.elbow = data[6];

    position.rightArm.handRot = data[10];
    position.rightArm.handAngle = data[12];

    position.head.headY = data[8];
    position.head.headX = data[9];
}

/**
 * @brief Parses robotPosition to raw data.
 * 
 * @param position 
 * @param data 
 */
void toRawData(robotPosition position, char data[25]) {
    data[1] = position.leftArm.armY;
    data[3] = position.leftArm.armX;
    data[5] = position.leftArm.armRot;

    data[7] = position.leftArm.elbow;

    data[11] = position.leftArm.handRot;
    data[13] = position.leftArm.handAngle;

    data[0] = position.rightArm.armY;
    data[2] = position.rightArm.armX;
    data[4] = position.rightArm.armRot;

    data[6] = position.rightArm.elbow;

    data[10] = position.rightArm.handRot;
    data[12] = position.rightArm.handAngle;

    data[8] = position.head.headY;
    data[9] = position.head.headX;
}
