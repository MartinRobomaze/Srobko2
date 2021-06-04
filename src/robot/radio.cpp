#include "radio.h"

Radio::Radio() {
    radio = new RF24(radioPin1, radioPin2, RF24_SPI_SPEED);

    radio->begin();
    delay(10);
    radio->setDataRate(RF24_250KBPS);
    radio->setPALevel(RF24_PA_LOW);
    radio->openWritingPipe(address);
    radio->openReadingPipe(1, address);

    radio->setChannel(0x66);
    radio->printDetails();
    radio->enableDynamicPayloads();
    radio->startListening();
}

Radio::~Radio() {
    delete radio;
}

bool Radio::readData(uint8_t *data) {
    uint8_t rawData[sizeof(data)];
    
    if (!radio->available()) {
        return false;
    }

    radio->read(rawData, sizeof(rawData));

    if (rawData[0] != controlNumber) {
        return false;
    }

    #ifdef DEBUG
    Serial.print("KC: ");
    Serial.print(int(rawData[0]));
    Serial.print(" U11: ");
    Serial.println(int(rawData[11]));
    Serial.print(" U12: ");
    Serial.println(int(rawData[12]));
    Serial.print(" U24: ");
    Serial.println(int(rawData[24]));
    #endif

    for (int i = 1; i < 26; i++) {
        data[i] = rawData[i];
    }

    return true;
}
