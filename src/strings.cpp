#include "strings.h"

#include <algorithm>
#include <cctype>

void trimStartInPlace(std::string &string) {
    auto it = string.begin();
    while (it != string.end() && std::isspace(*it)) it = string.erase(it);
}

void trimEndInPlace(std::string &string) {
    auto it = string.rbegin();
    while (it != string.rend() && std::isspace(*it)) it++;

    auto whitespaceIt = it.base();
    while (whitespaceIt != string.end()) whitespaceIt = string.erase(whitespaceIt);
}

void trimInPlace(std::string &string) {
    trimStartInPlace(string);
    trimEndInPlace(string);
}

void toLowerCaseInPlace(std::string &string) {
    std::transform(string.begin(), string.end(), string.begin(), ::tolower);
}

void toUpperCaseInPlace(std::string &string) {
    std::transform(string.begin(), string.end(), string.begin(), ::toupper);
}

std::string trimStart(std::string string) {
    trimStartInPlace(string);
    return string;
}

std::string trimEnd(std::string string) {
    trimEndInPlace(string);
    return string;
}

std::string trim(std::string string) {
    trimInPlace(string);
    return string;
}

std::string toLowerCase(std::string string) {
    toLowerCaseInPlace(string);
    return string;
}

std::string toUpperCase(std::string string) {
    toUpperCaseInPlace(string);
    return string;
}
