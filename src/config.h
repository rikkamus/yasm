#pragma once

#include <istream>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "length.h"
#include "text.h"

class ConfigParseException : public std::runtime_error {

private:

    unsigned int lineNumber;
    std::string reason;

public:

    ConfigParseException(unsigned int lineNumber, const std::string &reason);

};

class IniEntry {

private:

    unsigned int lineNumber;
    std::string value;

public:

    IniEntry();
    IniEntry(unsigned int lineNumber, const std::string &value);

    const std::string& stringValue() const;
    int intValue() const;
    float floatValue() const;
    bool boolValue() const;
    Dimension dimensionValue() const;

    unsigned int getLineNumber() const;

};

class IniConfig {

public:

    static const std::string DEFAULT_SECTION_NAME;

private:

    std::unordered_map<std::string, std::unordered_map<std::string, IniEntry>> entries;

public:

    IniConfig();

    void load(std::istream &stream);

    const IniEntry& get(const std::string &section, const std::string &key) const;
    bool contains(const std::string &section, const std::string &key) const;

    //Uses default section name
    const IniEntry& get(const std::string &key) const;

    //Uses default section name
    bool contains(const std::string &key) const;

};

struct Config {

    std::string formatString;
    Anchor anchor;
    Dimension offsetX;
    Dimension offsetY;
    int font;
    float opacity;
    float scale;
    bool hideVehicleName;
    bool hideWhenUsingPhone;

    Config();

    void load(std::istream &stream);

};
