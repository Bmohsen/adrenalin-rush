// adrenalin-rush.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "base.h"
#include "tank.h"
#include <vector>


const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 900;


void game_loop();
void login_screen();
void init_skrimish_world();

std::vector<BaseTank*> tanks;
LightTank t34;

int main()
{
    game_loop();
    return 0;
}

void game_loop() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AD Rush");
    // set fps to 60
    //SetTargetFPS(0);

    //init_skrimish_world();
    t34.loadTexture();
    t34.spawn(100, 100);
    while (!WindowShouldClose()) {
        t34.movement();
    
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("Run, Run, you little shit...", 0, 0, 20, BLACK);
        t34.draw();
        EndDrawing();
    }
    // Cleanup tanks and textures
    for (auto tank : tanks) {
        delete tank;
    }
    tanks.clear();
    CloseWindow();
}

void init_skrimish_world() {
    // Clear existing tanks if any
    for (auto tank : tanks) delete tank;
    tanks.clear();

    // Create tanks dynamically and add to vector
    tanks.push_back(new LightTank());
    tanks.back()->spawn(100, 100);

    tanks.push_back(new MediumTank());
    tanks.back()->spawn(300, 200);
}


void login_screen(){}