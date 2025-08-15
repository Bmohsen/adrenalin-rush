// adrenalin-rush.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "engine/base.hpp"
#include "engine/demo.hpp"
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

void game_loop()
{

    init_demo();
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        ClearBackground(WHITE);
        game_demo(dt);
        EndDrawing();
    }

    CloseWindow();
}

void login_screen() {}

void init_basics()
{
    std::string game_icon_path = get_asset("game_icon", AssetType::IMAGE);
    Image game_icon = LoadImage(game_icon_path.c_str());
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AD Rush");
    SetWindowIcon(game_icon);
    SetTargetFPS(60);
    InitAudioDevice();
}