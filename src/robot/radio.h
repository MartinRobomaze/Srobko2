#include <RF24.h>

class Radio {
    public:
        Radio();
        ~Radio();

        bool readData(uint8_t *data);
    private:
        RF24 *radio;
        const uint8_t radioPin1 = 41;
        const uint8_t radioPin2 = 42;

        const uint64_t address = 0xF0F0F0F0E1LL;

        const uint8_t controlNumber = 159;
};
