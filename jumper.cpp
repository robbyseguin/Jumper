#include "raylib.h"

int main()
{

// Screen Size
const int screenWidth = 800;
const int screenHeight = 600;

//Player Variables
const int playerJumpHeight = 25;

//Player Texture
Texture2D player = LoadTexture("textures/scarfy.png");
Rectangle playerRect;
playerRect.width = player.width / 6;
playerRect.height = player.height;
playerRect.x = 0;
playerRect.y = 0;
Vector2 playerPos;
playerPos.x = screenWidth / 2 - playerRect.width / 2;
playerPos.y = screenHeight - playerRect.height;


// Game Engine Physics Variables
int velocity = 0;
int gravity = 1;

// is Conditions
bool isJumping = false;

// Window init
InitWindow(screenWidth, screenHeight, "Jumper");
SetTargetFPS(60);

while(!WindowShouldClose())
{   
    //Start Drawing
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    if(playerRect.y >= screenHeight - playerRect.height)
    {   
        // stop velocity
        velocity = 0;
        isJumping = false;
    }
    else
    {
    // update gravity
    velocity += gravity;
    isJumping = true;
    }
    
     if(IsKeyDown(KEY_SPACE) && !isJumping)
    {
        velocity -= playerJumpHeight;
    }

    // update Y position
    playerPos.y += velocity;
    DrawTextureRec(player, playerRect, playerPos, WHITE);

    //End Drawing
    EndDrawing();
}
UnloadTexture(player);
CloseWindow();  

}