#include "Utility.h"


uint8_t toggleClock(uint8_t clock) {
    uint8_t mask = 1;
    return clock ^= mask;
}