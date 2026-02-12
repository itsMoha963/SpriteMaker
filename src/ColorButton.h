#ifndef _COLOR_BUTTON_H
#define _COLOR_BUTTON_H
#include "Button.h"
class clsColorButton : public clsButton{
private:
Color color;
public:
clsColorButton(Rectangle r, Color c):clsButton(r),color(c) {}
void draw()const;
Color value()const{ return color;}
};
#endif