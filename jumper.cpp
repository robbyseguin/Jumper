#include "raylib.h"


struct AnimData
{
Rectangle rec;
Vector2 pos;
int frame;
float updateTime;
float runningTime;
};


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

AnimData hazardData
{
    {0.0f, 0.0f, hazard.width / 8, hazard.height / 8}, // Rectangle
    {screenWidth , screenHeight - hazard.height / 8},   // Vec2 Pos
    0, // Frame
    1.0f / 12.0f, // updateTime
    0.0f //running time
};

AnimData hazard2Data
{
    {0.0f, 0.0f, hazard.width / 8, hazard.height / 8}, // Rectangle
    {screenWidth + 300 , screenHeight - hazard.height / 8},   // Vec2 Pos
    0, // Frame
    1.0f / 16.0f, // updateTime
    0.0f //running time
};


//Hazard Velocity pixel per second
int hazardVelocity = -200;

//Player Texture
Texture2D player = LoadTexture("textures/scarfy.png");
AnimData playerData;
playerData.rec.width = player.width / 6;
playerData.rec.height = player.height;
playerData.rec.x = 0;
playerData.rec.y = 0;
playerData.pos.x = screenWidth / 2 - playerData.rec.width / 2;
playerData.pos.y = screenHeight - playerData.rec.height;
playerData.frame = 0;
playerData.updateTime = 1.0f / 12.0f;
playerData.runningTime = 0.0f;


//Set FPS
SetTargetFPS(60);

while(!WindowShouldClose())
{   
    float deltaTime = GetFrameTime();
    //Start Drawing
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    if(playerData.pos.y >= screenHeight - playerData.rec.height)
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
    hazardData.pos.x += hazardVelocity * deltaTime;

     // update Hazard2 X position
    hazard2Data.pos.x += hazardVelocity * deltaTime;

    // update Player Y position
    playerData.pos.y += velocity * deltaTime;

    //update running time
    playerData.runningTime += deltaTime;

    if(!isJumping)
    {
      if(playerData.runningTime >= playerData.updateTime)
    {

    playerData.runningTime = 0.0f;
    playerData.rec.x = playerData.frame * playerData.rec.width;
    playerData.frame++;

    if(playerData.frame > 5)
    {
        playerData.frame = 0;
    }
    }  
    }
  
   // Update hazardrunning time
    hazardData.runningTime += deltaTime;

   // Update hazard animation  
    if(hazardData.runningTime >= hazardData.updateTime)
    {

    hazardData.runningTime = 0.0f;
    hazardData.rec.x = hazardData.frame * hazardData.rec.width;
    hazardData.frame++;

    if(hazardData.frame > 7)
    {
        hazardData.frame = 0;
    }
    }  

    // Update hazardrunning time
    hazard2Data.runningTime += deltaTime;

   // Update hazard animation  
    if(hazard2Data.runningTime >= hazard2Data.updateTime)
    {

    hazard2Data.runningTime = 0.0f;
    hazard2Data.rec.x = hazard2Data.frame * hazard2Data.rec.width;
    hazard2Data.frame++;

    if(hazard2Data.frame > 7)
    {
        hazard2Data.frame = 0;
    }
    }  
    



    //Draw Hazard
    DrawTextureRec(hazard, hazardData.rec, hazardData.pos, WHITE);
     //Draw Hazard 2
    DrawTextureRec(hazard, hazard2Data.rec, hazard2Data.pos, RED);

    //Draw Player  
    DrawTextureRec(player, playerData.rec, playerData.pos, WHITE);

    //End Drawing
    EndDrawing();
}
UnloadTexture(player);
UnloadTexture(hazard);
CloseWindow();  

}