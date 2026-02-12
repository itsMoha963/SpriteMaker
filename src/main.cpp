#include <iostream>
#include <vector>
#include <raylib.h>
#include "ColorButton.h"
#include "Button.h"
#include "CanvasWindow.h"
#include "Global.h"
using namespace std; 

int main(){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SpriteMaker");
    SetTargetFPS(60);
    clsButton createNewBtn({10,10,100,30},"Create New");
    clsButton clearBtn({120,10,100,30},"Clear Canva");
    clsColorButton colorBtns[5] = {
        // xPos, yPos, 20x20px,  color,  isHovered?
        {{230, 10, 20, 20}, BLACK},
        {{255, 10, 20, 20}, WHITE},
        {{280, 10, 20, 20}, RED},
        {{305, 10, 20, 20}, GREEN},
        {{330, 10, 20, 20}, BLUE}
    };
    
    clsCanvasWindow canvas ({100, TOP_BAR_HEIGHT + 50, 800, 485});
    
    int drawWidth = (int)canvas.rectBounds().width;
    int drawHeight = (int)canvas.rectBounds().height - TITLE_BAR_HEIGHT;
    int GRID_WIDTH = drawWidth / PIXEL_SIZE;
    int GRID_HEIGHT = drawHeight / PIXEL_SIZE;



    vector<vector<Color>> vPixels(GRID_HEIGHT,vector<Color>(GRID_WIDTH,WHITE));
    Color currentColor = BLACK;
    // ColorCanva(vPixels,WHITE,GRID_HEIGHT,GRID_WIDTH);
    while (WindowShouldClose() == false){
        Vector2 mousePos = GetMousePosition();
        // updating the ui
        createNewBtn.update(mousePos);
        clearBtn.update(mousePos);
        for(auto& colorbutton : colorBtns) colorbutton.update(mousePos);

        if(createNewBtn.clicked())
            canvas.open(); // convert isOpen to true
        if(clearBtn.clicked()&& canvas.openState())// checks if clearbtn is clicked and if the canva is open
        {
            canvas.clearCanva(GRID_HEIGHT,GRID_WIDTH,vPixels);
        }
        
        for(auto& colorbtn: colorBtns){
            if(colorbtn.clicked())
                currentColor = colorbtn.value();
        }


        if (canvas.openState() && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Rectangle area = canvas.drawArea();
            if (CheckCollisionPointRec(mousePos, area)) {
                int gx = (int)((mousePos.x - area.x) / PIXEL_SIZE);
                int gy = (int)((mousePos.y - area.y) / PIXEL_SIZE);
                if (gx >= 0 && gx < GRID_WIDTH && gy >= 0 && gy < GRID_HEIGHT)
                    vPixels[gy][gx] = currentColor;
            }
        }

        BeginDrawing();
        ClearBackground(DARKBLUE);
        DrawRectangle(0,0,SCREEN_WIDTH, SCREEN_HEIGHT/14, SKYBLUE);

        createNewBtn.draw();
        clearBtn.draw();
        for (const auto& cb : colorBtns) cb.draw();

        canvas.drawWindow();
        canvas.drawPixels(vPixels, GRID_HEIGHT, GRID_WIDTH);
        canvas.drawGridLines(GRID_HEIGHT, GRID_WIDTH);

        EndDrawing();
    }

    CloseWindow();
}
