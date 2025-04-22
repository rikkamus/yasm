#pragma once

#include <string>

enum class LengthUnit {

    PIXELS,
    VIEWPORT_WIDTH,
    VIEWPORT_HEIGHT

};

struct Dimension {

    static Dimension parse(const std::string &string);

    float amount;
    LengthUnit unit;

    Dimension(float amount, LengthUnit unit);

    Dimension convertTo(LengthUnit unit) const;

};
