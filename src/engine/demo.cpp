// demo.cpp
#include "tank.hpp"
#include "player.hpp"
#include "demo.hpp"
#include <vector>

using namespace Engine;

// Persistent demo objects
static LightTank *playerTank = nullptr;
static Player::Player *player = nullptr;
static std::vector<BaseTank *> npcTanks;

void init_demo()
{
    if (!playerTank)
    {
        // Spawn player tank at default position
        playerTank = new LightTank();
        playerTank->spawn(600, 700); // SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.7
        player = new Player::Player(playerTank);

        // Spawn a few NPC tanks
        LightTank *npc1 = new LightTank();
        npc1->spawn(100, 100);
        npcTanks.push_back(npc1);

        LightTank *npc2 = new LightTank();
        npc2->spawn(400, 200);
        npcTanks.push_back(npc2);
    }
}

void game_demo(float dt)
{
    init_demo(); // Ensure everything is initialized once
    BeginMode2D(player->camera);
    // Update player
    player->updateControl(dt);

    // Draw player
    player->draw();

    // Draw NPC tanks
    for (auto t : npcTanks)
    {
        t->draw();
        // --- Draw All Explosions Globally on Top ---
        for (auto *sys : Engine::Animation::ExplostionSystem::global_explosions)
        {
            sys->draw();
        }
    }
    EndMode2D();
}
