#include "MathHelper.h"
#include <cmath>

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif // !M_PI


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