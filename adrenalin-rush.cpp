// adrenalin-rush.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "engine/base.h"
#include "engine/tank.h"
#include "engine/player.h"
#include <vector>


const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 900;


void game_loop();
void login_screen();
void init_skrimish_world();

std::vector<BaseTank*> tanks;
Player* playerTank = nullptr;

int main()
{
    game_loop();
    return 0;
}

void game_loop() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AD Rush");
    // set fps to 60
    SetTargetFPS(60);
    playerTank = new Player();
    // init tank state 
   
    while (!WindowShouldClose()) {
     
    
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("Run, Run, you little shit...", 0, 0, 20, BLACK);
   
        EndDrawing();
    }
    // Cleanup tanks and textures
    for (auto tank : tanks) {
        delete tank;
    }
    tanks.clear();
    CloseWindow();
}


void login_screen(){}