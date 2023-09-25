#include "raylib.h"

int main()
{
// Screen Size
const int screenWidth = 800;
const int screenHeight = 600;

//Player Variables ( Pixels/Second)
const int playerJumpHeight = -550;

// Game Engine Physics Variables (Pixels/Second)
int velocity = 0;
int gravity = 1000;

// is Conditions
bool isJumping = false;

// Window init
InitWindow(screenWidth, screenHeight, "Jumper");

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



//Set FPS
SetTargetFPS(60);

while(!WindowShouldClose())
{   
    float deltaTime = GetFrameTime();
    //Start Drawing
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    if(playerPos.y >= screenHeight - playerRect.height)
    {   
        // stop velocity
        velocity = 0;
        isJumping = false;
    }
    else
    {
    // update gravity
    velocity += gravity * deltaTime;
    isJumping = true;
    }
    
     if(IsKeyDown(KEY_SPACE) && !isJumping)
    {
        velocity += playerJumpHeight;
    }

    // update Y position
    playerPos.y += velocity * deltaTime;
    
    DrawTextureRec(player, playerRect, playerPos, WHITE);

    //End Drawing
    EndDrawing();
}
UnloadTexture(player);
CloseWindow();  

}