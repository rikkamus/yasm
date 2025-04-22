#include "config.h"

#include "speed.h"
#include "strings.h"
#include "utils.h"

using namespace std::string_literals;

ConfigParseException::ConfigParseException(unsigned int lineNumber, const std::string &reason)
    : std::runtime_error("Config parse error at line "s + std::to_string(lineNumber) + ": "s + reason),
      lineNumber(lineNumber), reason(reason) {

}

IniEntry::IniEntry() : IniEntry(0, "") {

}

IniEntry::IniEntry(unsigned int lineNumber, const std::string &value) : lineNumber(lineNumber), value(value) {

}

const std::string& IniEntry::stringValue() const {
    return this->value;
}

int IniEntry::intValue() const {
    try {
        return parseInt(this->value);
    } catch (const std::exception &/*ignored*/) {
        throw ConfigParseException(this->lineNumber, "Value is not a valid integer.");
    }
}

float IniEntry::floatValue() const {
    try {
        return parseFloat(this->value);
    } catch (const std::exception &/*ignored*/) {
        throw ConfigParseException(this->lineNumber, "Value is not a valid float.");
    }
}

bool IniEntry::boolValue() const {
    try {
        return parseBool(this->value);
    } catch (const std::exception &/*ignored*/) {
        throw ConfigParseException(this->lineNumber, "Value is not a valid boolean.");
    }
}

Dimension IniEntry::dimensionValue() const {
    try {
        return Dimension::parse(this->value);
    } catch (const std::exception &/*ignored*/) {
        throw ConfigParseException(this->lineNumber, "Value is not a valid dimension.");
    }
}

unsigned int IniEntry::getLineNumber() const {
    return this->lineNumber;
}

const std::string IniConfig::DEFAULT_SECTION_NAME = "";

IniConfig::IniConfig() {

}

void IniConfig::load(std::istream &stream) {
    this->entries.clear();

    std::string section = IniConfig::DEFAULT_SECTION_NAME;
    std::string line;
    unsigned int lineNumber = 0;

    while (std::getline(stream, line)) {
        trimInPlace(line);
        lineNumber++;

        //Handle empty lines and comments
        if (line.empty() || line.starts_with("#") || line.starts_with(";") || line.starts_with("//")) continue;

        //Handle section names
        if (line.starts_with("[")) {
            if (!line.ends_with("]")) throw ConfigParseException(lineNumber, "Invalid section declaration");
            section = trim(line.substr(1, line.length() - 2));
            continue;
        }

        //Handle key-value pairs
        size_t equalsSignIndex = line.find('=');
        if (equalsSignIndex == std::string::npos) throw ConfigParseException(lineNumber, "Invalid line type");

        std::string key = toLowerCase(trim(line.substr(0, equalsSignIndex)));
        if (key.empty()) throw ConfigParseException(lineNumber, "Key must not be empty");

        std::string value = toLowerCase(trim(line.substr(equalsSignIndex + 1, line.length() - equalsSignIndex - 1)));
        
        this->entries[section][key] = IniEntry(lineNumber, value);
    }
}

const IniEntry& IniConfig::get(const std::string &section, const std::string &key) const {
    return this->entries.at(toLowerCase(section)).at(toLowerCase(key));
}

bool IniConfig::contains(const std::string &section, const std::string &key) const {
    const std::string lowerCaseSection = toLowerCase(section);
    return this->entries.contains(lowerCaseSection) && this->entries.at(lowerCaseSection).contains(toLowerCase(key));
}

const IniEntry& IniConfig::get(const std::string &key) const {
    return get(IniConfig::DEFAULT_SECTION_NAME, key);
}

bool IniConfig::contains(const std::string &key) const {
    return contains(IniConfig::DEFAULT_SECTION_NAME, key);
}

Config::Config()
    : formatString("<font size='60'>%mph ~b~mph"), anchor(Anchor::BOTTOM_RIGHT),
      offsetX(Dimension(15.0f, LengthUnit::VIEWPORT_HEIGHT)), offsetY(Dimension(15.0f, LengthUnit::VIEWPORT_HEIGHT)),
      font(0), opacity(1.0f), scale(1.0f), hideVehicleName(true), hideWhenUsingPhone(true) {

}

void Config::load(std::istream &stream) {
    IniConfig config;
    config.load(stream);

    if (config.contains("Format")) {
        IniEntry entry = config.get("Format");
        if (!validateFormat(entry.stringValue())) throw ConfigParseException(entry.getLineNumber(), "Invalid format string.");
        this->formatString = entry.stringValue();
    }

    if (config.contains("Anchor")) {
        IniEntry entry = config.get("Anchor");
        std::string anchor = toLowerCase(entry.stringValue());

        if (anchor == "topleft") this->anchor = Anchor::TOP_LEFT;
        else if (anchor == "topright") this->anchor = Anchor::TOP_RIGHT;
        else if (anchor == "bottomleft") this->anchor = Anchor::BOTTOM_LEFT;
        else if (anchor == "bottomright") this->anchor = Anchor::BOTTOM_RIGHT;
        else throw ConfigParseException(entry.getLineNumber(), "Invalid anchor");
    }

    if (config.contains("OffsetX")) this->offsetX = config.get("OffsetX").dimensionValue();
    if (config.contains("OffsetY")) this->offsetY = config.get("OffsetY").dimensionValue();
    if (config.contains("Font")) this->font = config.get("Font").intValue();

    if (config.contains("Opacity")) {
        IniEntry entry = config.get("Opacity");
        float opacity = entry.floatValue();
        if (opacity < 0.0f || opacity > 1.0f) throw ConfigParseException(entry.getLineNumber(), "Opacity must be a float between 0 and 1.");
        this->opacity = opacity;
    }

    if (config.contains("Scale")) {
        IniEntry entry = config.get("Scale");
        float scale = entry.floatValue();
        if (scale < 0.0f) throw ConfigParseException(entry.getLineNumber(), "Scale must be a positive float.");
        this->scale = scale;
    }

    if (config.contains("HideVehicleName")) this->hideVehicleName = config.get("HideVehicleName").boolValue();
    if (config.contains("HideWhenUsingPhone")) this->hideWhenUsingPhone = config.get("HideWhenUsingPhone").boolValue();
}
