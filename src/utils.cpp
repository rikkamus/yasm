#include "utils.h"

#include <cctype>
#include <stdexcept>

#include "strings.h"

int parseInt(const std::string &string) {
    for (auto it = string.cbegin(); it != string.cend(); it++) {
        if ((*it == '+' || *it == '-')) {
            if (it != string.cbegin()) throw std::invalid_argument("Invalid integer.");
            continue;
        }

        if (!std::isdigit(*it)) throw std::invalid_argument("Invalid integer.");
    }

    return std::stoi(string);
}

float parseFloat(const std::string &string) {
    bool dotEncountered = false;

    for (auto it = string.cbegin(); it != string.cend(); it++) {
        if ((*it == '+' || *it == '-')) {
            if (it != string.cbegin()) throw std::invalid_argument("Invalid float.");
            continue;
        }

        if (*it == '.') {
            if (dotEncountered) throw std::invalid_argument("Invalid float.");
            dotEncountered = true;
            continue;
        }

        if (!std::isdigit(*it)) throw std::invalid_argument("Invalid float.");
    }

    return std::stof(string);
}

bool parseBool(const std::string &string) {
    std::string lowerCaseValue = toLowerCase(string);

    if (lowerCaseValue == "true") {
        return true;
    } else if (lowerCaseValue == "false") {
        return false;
    } else {
        throw std::invalid_argument("Invalid boolean.");
    }
}
