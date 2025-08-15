#pragma once
#include <vector>
#include <string>
#include <raylib.h>

namespace Engine {

    enum class TileType {
        WATER,
        DIRT,
        GRASS,
        COUNT
    };

    class WorldGenerator {
    public:
        WorldGenerator(int width, int height, float noiseScale);

        void generate();
        void draw(const Vector2& cameraPos);

        TileType getTile(int x, int y) const;

    private:
        int width;
        int height;
        float noiseScale;

        std::vector<std::vector<TileType>> tiles;

        Texture2D tileTextures[(int)TileType::COUNT];

        float perlinNoise(float x, float y);

        void loadTileTextures();
    };

} 
