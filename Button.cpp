#include "Button.h"

void clsButton::update(Vector2 mousePos){
        this->isHovered_ = CheckCollisionPointRec(mousePos,rect);
 }

bool clsButton::clicked()const{
        return isHovered_ &&IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void clsButton::draw()const{
        Color bg = isHovered_ ? LIGHTGRAY:WHITE;
        DrawRectangleRec(rect,bg);
        DrawRectangleLinesEx(rect,1,DARKGRAY);
        int textWidth = MeasureText(text, 16);
        int textX = rect.x + (rect.width - textWidth)/2;
        int textY = rect.y + (rect.height - 16) /2;
        DrawText(text, textX, textY, 16, BLACK);
 }