#include "raylib.h"

int main()
{

// Screen Size
const int screenWidth = 800;
const int screenHeight = 600;

// Window init
InitWindow(screenWidth, screenHeight, "Jumper");
SetTargetFPS(60);

while(!WindowShouldClose())
{   
    //Start Drawing
    BeginDrawing();
    ClearBackground(RAYWHITE);

    //End Drawing
    EndDrawing();
}    

}