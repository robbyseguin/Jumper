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

//Hazard Texture
Texture2D hazard = LoadTexture("textures/12_nebula_spritesheet.png");
Rectangle hazardRect = {0.0f, 0.0f, hazard.width / 8, hazard.height / 8};
Vector2 hazardPos = {screenWidth , screenHeight - hazardRect.height};
int hazardFrame = 0;
const float hazardUpdateTime = 1.0f / 12.0f;
float hazardRunningTime = 0.0f; 


//Hazard Velocity pixel per second
int hazardVelocity = -200;

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

//animation frame
int frame = 0;
// time before we update animation frame
const float updateTime = 1.0f / 12.0f;
float runningTime = 0.0f;


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

    // update Hazard X position
     hazardPos.x += hazardVelocity * deltaTime;

    // update Player Y position
    playerPos.y += velocity * deltaTime;

    //update running time
    runningTime += deltaTime;

    if(!isJumping)
    {
      if(runningTime >= updateTime)
    {

    runningTime = 0.0f;
    playerRect.x = frame * playerRect.width;
    frame++;

    if(frame > 5)
    {
        frame = 0;
    }
    }  
    }
  
   // Update hazardrunning time
    hazardRunningTime += deltaTime;

   // Update hazard animation  
    if(hazardRunningTime >= hazardUpdateTime)
    {

    hazardRunningTime = 0.0f;
    hazardRect.x = hazardFrame * hazardRect.width;
    hazardFrame++;

    if(hazardFrame > 7)
    {
        hazardFrame = 0;
    }
    }  
    



    //Draw Hazard
    DrawTextureRec(hazard, hazardRect, hazardPos, WHITE);


    //Draw Player  
    DrawTextureRec(player, playerRect, playerPos, WHITE);

    //End Drawing
    EndDrawing();
}
UnloadTexture(player);
UnloadTexture(hazard);
CloseWindow();  

}