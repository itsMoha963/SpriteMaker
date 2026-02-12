#include "CanvasWindow.h"
   
    
void clsCanvasWindow::drawWindow() const {
        if (!isOpen) return;
        DrawRectangle(rect.x + 5, rect.y + 5, rect.width, rect.height, Fade(BLACK, 0.3f));
        DrawRectangleRec(rect, WHITE);
        DrawRectangle(rect.x, rect.y, rect.width, TITLE_BAR_HEIGHT, LIGHTGRAY);
        DrawText("New Canvas", rect.x + 10, rect.y + 5, 16, BLACK);
        DrawRectangleLinesEx(rect, 2, DARKGRAY);
}

void clsCanvasWindow::drawPixels(const std::vector<std::vector<Color>>& pixels, int gridH, int gridW) const {
        if (!isOpen) return;
        for (int y = 0; y < gridH; ++y) {
            for (int x = 0; x < gridW; ++x) {
                int px = rect.x + x * PIXEL_SIZE;
                int py = rect.y + TITLE_BAR_HEIGHT + y * PIXEL_SIZE;
                DrawRectangle(px, py, PIXEL_SIZE, PIXEL_SIZE, pixels[y][x]);
            }
        }
 }




void clsCanvasWindow::drawGridLines(int gridH, int gridW) const {
        if (!isOpen) return;
        for (int x = 0; x <= gridW; ++x) {
            int lx = rect.x + x * PIXEL_SIZE;
            DrawLine(lx, rect.y + TITLE_BAR_HEIGHT,
                     lx, rect.y + TITLE_BAR_HEIGHT + gridH * PIXEL_SIZE,
                     LIGHTGRAY);
        }
        for (int y = 0; y <= gridH; ++y) {
            int ly = rect.y + TITLE_BAR_HEIGHT + y * PIXEL_SIZE;
            DrawLine(rect.x, ly,
                     rect.x + gridW * PIXEL_SIZE, ly,
                     LIGHTGRAY);
        }
 }
 void clsCanvasWindow::clearCanva(int GRID_HEIGHT, int GRID_WIDTH ,std::vector<std::vector<Color>> &vPixels){
    for (int y = 0; y < GRID_HEIGHT; ++y)
                for (int x = 0; x < GRID_WIDTH; ++x)
                    vPixels[y][x] = WHITE;
 }