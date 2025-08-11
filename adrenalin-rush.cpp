// adrenalin-rush.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "engine/base.h"
#include "engine/tank.h"
#include "engine/Player.h"
#include <vector>

using namespace Engine;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 900;


void game_loop();
void login_screen();
void init_basics();

int main()
{
    init_basics();
    game_loop();
    return 0;
}

void game_loop() {
   
    BaseTank* lightTank = new LightTank();
    // init tank state 
    lightTank->loadTexture("m6");
    lightTank->spawn(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.7);
    Player* player = new Player(lightTank);
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        player->updateControl(dt);
        BeginDrawing();
        ClearBackground(WHITE);
        player->draw();
        EndDrawing();
    }
    // Cleanup tanks and textures
    delete player;
    CloseWindow();
}


void login_screen(){}

void init_basics() {
    std::string game_icon_path = get_asset("game_icon", AssetType::IMAGE);
    Image game_icon = LoadImage(game_icon_path.c_str());
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AD Rush");
    SetWindowIcon(game_icon);
    SetTargetFPS(60);
    InitAudioDevice();
}