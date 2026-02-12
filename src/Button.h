#ifndef _BUTTON_H
#define _BUTTON_H
#include <raylib.h>
class clsButton{
private:
    Rectangle rect;
    const char * text; // i cant use string like whaaat so i need to use char *
    bool isHovered_ = false;
public:
    clsButton(Rectangle rect, const char* text): rect(rect),text(text){}
    clsButton(Rectangle rect): rect(rect){}
    void update(Vector2 mousePos);
    bool clicked() const;
    virtual void draw() const;

    bool isHovered()const{ return isHovered_;}
    Rectangle rectBounds()const { return rect;}
};

#endif