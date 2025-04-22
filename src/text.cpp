#include "text.h"

#include "sdk/inc/natives.h"

static float relativeToGlobalPositionX(Anchor anchor, float relativePosX) {
    return (anchor == Anchor::TOP_LEFT || anchor == Anchor::BOTTOM_LEFT) ? relativePosX : (1 - relativePosX);
}

static float relativeToGlobalPositionY(Anchor anchor, float relativePosY) {
    return (anchor == Anchor::TOP_LEFT || anchor == Anchor::TOP_RIGHT) ? relativePosY :  (1 - relativePosY);
}

TextStyle::TextStyle() : font(0), alpha(255), center(false), scale(0.5f) {

}

void renderText(const std::string& text, Anchor anchor, Dimension offsetX, Dimension offsetY, const TextStyle &style) {
    float relativePosX = offsetX.convertTo(LengthUnit::VIEWPORT_WIDTH).amount / 100.0f;
    float relativePosY = offsetY.convertTo(LengthUnit::VIEWPORT_HEIGHT).amount / 100.0f;

    UI::SET_TEXT_FONT(style.font);
    UI::SET_TEXT_COLOUR(255, 255, 255, style.alpha);
    UI::SET_TEXT_CENTRE(style.center ? TRUE : FALSE);
    UI::SET_TEXT_SCALE(0.0f, style.scale);
    UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
    UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
    UI::SET_TEXT_OUTLINE();

    if (anchor == Anchor::TOP_LEFT || anchor == Anchor::BOTTOM_LEFT) {
        UI::SET_TEXT_WRAP(0.0f, 1.0f);
        UI::SET_TEXT_JUSTIFICATION(1);
    } else {
        UI::SET_TEXT_WRAP(0.0f, 1.0f - relativePosX);
        UI::SET_TEXT_JUSTIFICATION(2);
    }

    UI::_SET_TEXT_ENTRY((char*) "STRING");
    UI::_ADD_TEXT_COMPONENT_STRING((char*) text.c_str());
    UI::_DRAW_TEXT(relativeToGlobalPositionX(anchor, relativePosX), relativeToGlobalPositionY(anchor, relativePosY));
}
