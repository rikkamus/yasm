#include "length.h"

#include <stdexcept>

#include "sdk/inc/natives.h"

#include "utils.h"

Dimension Dimension::parse(const std::string &string) {
    std::string amountString;
    LengthUnit unit;

    if (string.ends_with("px")) {
        amountString = string.substr(0, string.length() - 2);
        unit = LengthUnit::PIXELS;
    } else if (string.ends_with("vw")) {
        amountString = string.substr(0, string.length() - 2);
        unit = LengthUnit::VIEWPORT_WIDTH;
    } else if (string.ends_with("vh")) {
        amountString = string.substr(0, string.length() - 2);
        unit = LengthUnit::VIEWPORT_HEIGHT;
    } else {
        amountString = string;
        unit = LengthUnit::PIXELS;
    }

    return Dimension(parseFloat(amountString), unit);
}

Dimension::Dimension(float amount, LengthUnit unit) : amount(amount), unit(unit) {

}

Dimension Dimension::convertTo(LengthUnit unit) const {
    int screenWidth, screenHeight;
    GRAPHICS::_GET_SCREEN_ACTIVE_RESOLUTION(&screenWidth, &screenHeight);

    if (this->unit == LengthUnit::PIXELS) {
        switch (unit) {
            case LengthUnit::PIXELS: return *this;
            case LengthUnit::VIEWPORT_WIDTH: return Dimension(this->amount / screenWidth * 100.0f, LengthUnit::VIEWPORT_WIDTH);
            case LengthUnit::VIEWPORT_HEIGHT: return Dimension(this->amount / screenHeight * 100.0f, LengthUnit::VIEWPORT_HEIGHT);
            default: throw std::logic_error("Unknown length unit.");
        }
    } else if (unit == LengthUnit::PIXELS) {
        switch (this->unit) {
            case LengthUnit::PIXELS: return *this;
            case LengthUnit::VIEWPORT_WIDTH: return Dimension(this->amount / 100.0f * screenWidth, LengthUnit::PIXELS);
            case LengthUnit::VIEWPORT_HEIGHT: return Dimension(this->amount / 100.0f * screenHeight, LengthUnit::PIXELS);
            default: throw std::logic_error("Unknown length unit.");
        }
    } else {
        return convertTo(LengthUnit::PIXELS).convertTo(unit);
    }
}
