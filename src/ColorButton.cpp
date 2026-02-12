#include "ColorButton.h"

void clsColorButton::draw()const{
    DrawRectangleRec(rectBounds(),color);
    float thickness = isHovered() ? 3.f : 1.f;
    DrawRectangleLinesEx(rectBounds(),thickness,BLACK);
}