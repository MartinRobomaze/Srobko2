#include "radio.h"

Radio::Radio() {
    radio = new RF24(cePin, csnPin, RF24_SPI_SPEED);

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

Radio::Radio(uint8_t _cePin, uint8_t _csnPin) {
    radio = new RF24(_cePin, _csnPin, RF24_SPI_SPEED);

    cePin = _cePin;
    csnPin = _csnPin;

    radio->begin();
    delay(10);
    radio->setDataRate(RF24_250KBPS);
    radio->setPALevel(RF24_PA_LOW);
    radio->openWritingPipe(address);
    radio->openReadingPipe(1, address);

    radio->setChannel(0x66);
    
    #ifdef DEBUG
    radio->printDetails();
    #endif

    radio->enableDynamicPayloads();
    radio->startListening();
}

bool Radio::readData(RobotPosition &position) {
    uint8_t rawData[26];
    
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

    uint8_t data[25];

    for (int i = 0; i < 25; i++) {
        data[i] = rawData[i+1];
    }

    position.parseRawData(data);

    return true;
}

Radio::~Radio() {
    delete radio;
}
