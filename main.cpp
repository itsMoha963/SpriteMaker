#include <iostream>
#include <vector>
#include <raylib.h>

using namespace std; 
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 700;
const int TOP_BAR_HEIGHT = 50;
const int PIXEL_SIZE = 20;
const int TITLE_BAR_HEIGHT = 25;

struct Button{
    Rectangle rect;
    const char * text; // i cant use string like whaaat so i need to use char *
    bool isHovered;
};
struct ColorButton{
    Rectangle rect;
    Color color;
    bool isHovered;
};
struct CanvasWindow{
    Rectangle rect;
    bool isOpen;
};
 ColorButton colorBtns[5] = {
     // xPos, yPos, 20x20px,  color,  isHovered?
    {{230, 10, 20, 20}, BLACK, false},
    {{255, 10, 20, 20}, WHITE, false},
    {{280, 10, 20, 20}, RED, false},
    {{305, 10, 20, 20}, GREEN, false},
    {{330, 10, 20, 20}, BLUE, false}
};
Color currentColor = BLACK; 

bool isButtonClicked(Button& button){
    Vector2 mousePos = GetMousePosition();
    button.isHovered = CheckCollisionPointRec(mousePos,button.rect);
    return button.isHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}
void DrawButton(Button &button){
    Color bgColor = button.isHovered ? LIGHTGRAY:WHITE;
    DrawRectangleRec(button.rect,bgColor);
    DrawRectangleLinesEx(button.rect, 1,DARKGRAY);

    int textWidth = MeasureText(button.text, 16);
    int textX = button.rect.x + (button.rect.width - textWidth)/2;
    int textY = button.rect.y + (button.rect.height - 16) /2;
    DrawText(button.text, textX, textY, 16, BLACK);

}

void DrawColorButton(ColorButton &button){
    DrawRectangleRec(button.rect, button.color);
    float thickness = button.isHovered ? 3 : 1;
    DrawRectangleLinesEx(button.rect, thickness, BLACK);
}

bool isColorButtonClicked(ColorButton &button){
    Vector2 mousePos = GetMousePosition();
    button.isHovered = CheckCollisionPointRec(mousePos, button.rect);
    return button.isHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void ColorCanva(vector<vector<Color>> &vPixels, Color color, int GRID_HEIGHT,int GRID_WIDTH){
    for(int y = 0; y < GRID_HEIGHT;y++){
        for(int x = 0 ; x<GRID_WIDTH;x++){
            vPixels[y][x]= color;
        }
    }
}

void DrawPixels(vector<vector<Color>> &vPixels, CanvasWindow &canvas, int GRID_HEIGHT,int GRID_WIDTH){
for(int y = 0; y <GRID_HEIGHT; y++){
    for(int x = 0; x <GRID_WIDTH; x++){
        // converting the pixels to screensize uhh
        int pixelX = canvas.rect.x + ( x * PIXEL_SIZE);
        int pixelY = canvas.rect.y + TITLE_BAR_HEIGHT + (y * PIXEL_SIZE);
        
        // update the pixel on screen
        DrawRectangle(pixelX,pixelY,PIXEL_SIZE, PIXEL_SIZE, vPixels[y][x]);
    }
}
};

void DrawGridLines(CanvasWindow &canvas, int GRID_HEIGHT,int GRID_WIDTH){
    for(int x = 0; x <= GRID_WIDTH; x++){
        int lineX = canvas.rect.x +(x * PIXEL_SIZE);
                // startpos of x and y and also endpos of x and y
                // i start after the title bar cuz there is no canva to draw on  
        DrawLine(lineX, canvas.rect.y + TITLE_BAR_HEIGHT, 
                 lineX, canvas.rect.y + TITLE_BAR_HEIGHT + (GRID_HEIGHT * PIXEL_SIZE), 
                 LIGHTGRAY);

    }
    for(int y = 0; y<= GRID_HEIGHT; y++){
        int lineY = canvas.rect.y + TITLE_BAR_HEIGHT + (y * PIXEL_SIZE);

        DrawLine(canvas.rect.x,lineY,canvas.rect.x + (GRID_WIDTH * PIXEL_SIZE), 
        lineY,LIGHTGRAY);
    }

}
int main()
{


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SpriteMaker");
    SetTargetFPS(60);
    Button createNewBtn = {
        { 10, 10, 100, 30 },  // x, y, width, height
        "Create New",
        false
    };

    Button ClearBtn = {
        {120,10,100,30},
        "Clear Canva",
        false
    };


    CanvasWindow canvas = {
         { 100, TOP_BAR_HEIGHT + 50, 800, 485},  // centered white canvas // title bar get 25px of the screen so its 475
        false
    };

    int canvasDrawAreaWidth = canvas.rect.width;
    int canvasDrawAreaHeight = canvas.rect.height - TITLE_BAR_HEIGHT;

    int GRID_WIDTH = canvasDrawAreaWidth / PIXEL_SIZE;
    int GRID_HEIGHT = canvasDrawAreaHeight / PIXEL_SIZE;

    vector<vector<Color>> vPixels(GRID_HEIGHT,vector<Color>(GRID_WIDTH,WHITE));
    // ColorCanva(vPixels,WHITE,GRID_HEIGHT,GRID_WIDTH);
    while (WindowShouldClose() == false){
        
        for(int i = 0; i < 5; i++){
            if(isColorButtonClicked(colorBtns[i])){
                currentColor = colorBtns[i].color;
            }
        }

        if(isButtonClicked(createNewBtn)){
            canvas.isOpen = true;
        }

        if(isButtonClicked(ClearBtn) && canvas.isOpen){
            ColorCanva(vPixels,WHITE,GRID_HEIGHT,GRID_WIDTH);
        }
        if(canvas.isOpen && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            Vector2 mousePos = GetMousePosition();

            Rectangle drawArea = {
                canvas.rect.x,
                canvas.rect.y + TITLE_BAR_HEIGHT,
                canvas.rect.width,
                canvas.rect.height - TITLE_BAR_HEIGHT

            };

            if(CheckCollisionPointRec(mousePos,drawArea)){
                int gridX = (mousePos.x - drawArea.x)/ PIXEL_SIZE;
                int gridY = (mousePos.y - drawArea.y)/ PIXEL_SIZE;

                if(gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT)
                    vPixels[gridY][gridX] = currentColor;
            }
        }

        BeginDrawing();
        ClearBackground(DARKBLUE);
        DrawRectangle(0,0,SCREEN_WIDTH, SCREEN_HEIGHT/14,SKYBLUE);

        DrawButton(createNewBtn); // creates a button with the name create new
        DrawButton(ClearBtn);

        for(int i = 0; i < 5; i++){
            DrawColorButton(colorBtns[i]);
        }
        if(canvas.isOpen){
            // drawing shadow to the left and dropshadow down
            DrawRectangle(canvas.rect.x+5,canvas.rect.y +5,canvas.rect.width,canvas.rect.height,Fade(BLACK,0.3f));
            // actual canva
            DrawRectangleRec(canvas.rect, WHITE);
           
            
            DrawRectangle(canvas.rect.x, canvas.rect.y, 
                         canvas.rect.width, 25, LIGHTGRAY);
            DrawText("New Canvas", canvas.rect.x + 10, canvas.rect.y + 5, 16, BLACK);


            //drawing
            DrawPixels(vPixels,canvas,GRID_HEIGHT,GRID_WIDTH);
            // grid guidlines
            DrawGridLines(canvas,GRID_HEIGHT,GRID_WIDTH);

            // border of canva
            DrawRectangleLinesEx(canvas.rect,2, DARKGRAY);
            

        }
        //DrawRectangle(SCREEN_WIDTH / 2, 0, 0, SCREEN_HEIGHT/2, BLUE);
        //DrawCircle(100,50,20,SKYBLUE);
        //DrawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 75, SKYBLUE);

        EndDrawing();
    }

    CloseWindow();
}
