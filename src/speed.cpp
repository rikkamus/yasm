#include "speed.h"

#include <stdexcept>
#include <unordered_map>

enum class Token {

    SPEED_MPH,
    SPEED_KPH,
    SPEED_MPS,
    PERCENT_SIGN

};

static const std::unordered_map<std::string, Token> TOKEN_MAP = {
    {"%mph", Token::SPEED_MPH},
    {"%kph", Token::SPEED_KPH},
    {"%mps", Token::SPEED_MPS},
    {"%%", Token::PERCENT_SIGN}
};

static Token parseToken(const std::string& format, size_t &pos) {
    for (const auto &pair : TOKEN_MAP) {
        if (format.substr(pos, pair.first.length()) == pair.first) {
            pos += pair.first.length();
            return pair.second;
        }
    }

    throw std::runtime_error("Could not parse token");
}

static std::string formatToken(Token token, float mps) {
    switch (token) {
        case Token::SPEED_MPH:
            return std::to_string((int)(mps * 2.236936f));
        case Token::SPEED_KPH:
            return std::to_string((int)(mps * 3.6f));
        case Token::SPEED_MPS:
            return std::to_string((int)mps);
        case Token::PERCENT_SIGN:
            return "%";
        default:
            throw std::runtime_error("Could not format token");
    }
}

float getPedVehicleSpeedMps(const Ped& ped) {
    return ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_USING(ped));
}

std::string formatSpeed(const std::string& format, float mps) {
    std::string result = "";
    size_t i = 0;

    while (i < format.length()) {
        if (format[i] != '%') {
            result.push_back(format[i]);
            i++;
            continue;
        }

        result.append(formatToken(parseToken(format, i), mps));
    }

    return result;
}

bool validateFormat(const std::string &format) {
    try {
        formatSpeed(format, 0.0f);
        return true;
    } catch (const std::runtime_error &/*ignored*/) {
        return false;
    }
}
