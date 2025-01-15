#include "MathHelper.h"

int radToDegress(double radians)
{
    return static_cast<int>(radians * (180.0 / M_PI));
}

int getRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);

    return dis(gen);
}