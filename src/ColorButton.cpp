#include "ColorButton.h"

void clsColorButton::draw() const {
  DrawRectangleRec(rectBounds(), color);
  float thickness = isHovered() ? 3.f : 1.f;
  Color isHoveredColor = isHovered() ? GRAY : BLACK;
  DrawRectangleLinesEx(rectBounds(), thickness, isHoveredColor);
}
