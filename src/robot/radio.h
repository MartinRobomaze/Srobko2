#include <RF24.h>
#include "types.h"

class Radio {
    public:
        /**
         * @brief Construct a new Radio object
         * 
         */
        Radio();

        /**
         * @brief Construct a new Radio object.
         * 
         * @param cePin 
         * @param csnPin 
         */
        Radio(uint8_t cePin, uint8_t csnPin);

        /**
         * @brief Reads data from radio.
         * 
         * @param position 
         * @return true 
         * @return false 
         */
        bool readData(robotPosition &position);

        /**
         * @brief Destroy the Radio object.
         * 
         */
        ~Radio();
    private:
        RF24 *radio;

        uint8_t cePin = 41;
        uint8_t csnPin = 42;

        const uint64_t address = 0xF0F0F0F0E1LL;

        const uint8_t controlNumber = 159;
};
