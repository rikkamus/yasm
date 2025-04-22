#pragma once

#include <string>

#include "length.h"

enum class Anchor {

    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT

};

struct TextStyle {

    int font;
    int alpha;
    bool center;
    float scale;

    TextStyle();

};

void renderText(const std::string& text, Anchor anchor, Dimension offsetX, Dimension offsetY, const TextStyle &style);
