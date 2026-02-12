#ifndef CANVAS_WINDOW_H
#define CANVAS_WINDOW_H
#include <raylib.h>
#include "Global.h"
#include <vector>
class clsCanvasWindow{
private:
Rectangle rect;
bool isOpen = false;

public:
    clsCanvasWindow(Rectangle r): rect(r){}
    void open(){ isOpen = true;}
    bool openState()const{ return isOpen;}
    Rectangle drawArea() const{
         return { rect.x, rect.y + (float)TITLE_BAR_HEIGHT, rect.width, rect.height - (float)TITLE_BAR_HEIGHT };
    }

    void drawWindow()const;
    void drawPixels(const std::vector<std::vector<Color>> &vpixels, int gridHeight, int gridWidth) const;
    void drawGridLines(int gridHeight, int gridWidth)const;
    void clearCanva(int GRID_HEIGHT, int GRID_WIDTH, std::vector<std::vector<Color>> &vPixels);
    Rectangle rectBounds()const{ return rect;}
};
#endif