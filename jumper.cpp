#include "raylib.h"
#include <array>

struct AnimData
{
Rectangle rec;
Vector2 pos;
int frame;
float updateTime;
float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

void updatePlayerData(AnimData &player, bool &isJumping, int velocity, float deltaTime)
{

    // update Player Y position
    player.pos.y += velocity * deltaTime;

    //update running time
    player.runningTime += deltaTime;

    if(!isJumping)
    {
     if(player.runningTime >= player.updateTime)
     {

      player.runningTime = 0.0f;
      player.rec.x = player.frame * player.rec.width;
      player.frame++;

      if(player.frame > 5)
       {
        player.frame = 0;
       }
     }  
    }
}

int main()
{
// Screen Size
int windowDimensions[2] = {800, 600};

//Player Variables ( Pixels/Second)
const int playerJumpHeight = -550;

// Game Engine Physics Variables (Pixels/Second)
int velocity = 0;
int gravity = 1000;

// is Conditions
bool isJumping = false;

// Window init
InitWindow(windowDimensions[0], windowDimensions[1], "Jumper");

//Hazard Texture
Texture2D hazard = LoadTexture("textures/12_nebula_spritesheet.png");

const int sizeOfHazardArray = 6;
AnimData hazardArray[sizeOfHazardArray] = {};

for(int i = 0; i < sizeOfHazardArray; i++)
{
    hazardArray[i].rec.x = 0.0;
    hazardArray[i].rec.y = 0.0;
    hazardArray[i].rec.width = hazard.width / 8;
    hazardArray[i].rec.height = hazard.height / 8;
    hazardArray[i].pos.x = windowDimensions[0] + 300 * i;
    hazardArray[i].pos.y = windowDimensions[1] - hazard.height / 8;
    hazardArray[i].frame = 0;
    hazardArray[i].updateTime = 1.0f / 12.0f;
    hazardArray[i].runningTime = 0.0f;
    hazardArray[i].pos.x = windowDimensions[0] + 300 * i;
}

//Hazard Velocity pixel per second
int hazardVelocity = -200;

//Player Texture
Texture2D player = LoadTexture("textures/scarfy.png");
AnimData playerData;
playerData.rec.width = player.width / 6;
playerData.rec.height = player.height;
playerData.rec.x = 0;
playerData.rec.y = 0;
playerData.pos.x = windowDimensions[0] / 2 - playerData.rec.width / 2;
playerData.pos.y = windowDimensions[1] - playerData.rec.height;
playerData.frame = 0;
playerData.updateTime = 1.0f / 12.0f;
playerData.runningTime = 0.0f / 0.16f;


//Set FPS
SetTargetFPS(60);

while(!WindowShouldClose())
{   
    float deltaTime = GetFrameTime();
    //Start Drawing
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    if(isOnGround(playerData, windowDimensions[1]))
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

    for (int i = 0; i < sizeOfHazardArray; i++)
    {
        // update Hazard X position
    hazardArray[i].pos.x += hazardVelocity * deltaTime;

    }
  
  updatePlayerData(playerData, isJumping, velocity, deltaTime);
  
  for(int i = 0; i< sizeOfHazardArray; i++)
  {
    // Update hazardrunning time
    hazardArray[i].runningTime += deltaTime;

   // Update hazard animation  
    if(hazardArray[i].runningTime >= hazardArray[i].updateTime)
    {
        hazardArray[i].runningTime = 0.0f;
        hazardArray[i].rec.x = hazardArray[i].frame * hazardArray[i].rec.width;
        hazardArray[i].frame++;

        if(hazardArray[i].frame > 7)
        {
            hazardArray[i].frame = 0;
        }
    }
  }
 
    //Draw Hazards
    for(int i = 0; i < sizeOfHazardArray; i++)
    {
        DrawTextureRec(hazard, hazardArray[i].rec, hazardArray[i].pos, WHITE);
    }
    //Draw Player  
    DrawTextureRec(player, playerData.rec, playerData.pos, WHITE);

    //End Drawing
    EndDrawing();
}
UnloadTexture(player);
UnloadTexture(hazard);
CloseWindow();  

}