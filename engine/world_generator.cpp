#include "world_generator.h"
#include "base.h"
#include <cmath>



namespace Engine {

    // Simple Perlin noise implementation helper
    static int permutation[] = { 151,160,137,91,90,15,
        // (repeat the 256 permutation values twice)
        151,160,137,91,90,15, /*... fill in the rest or reuse a known permutation table ...*/ };

    static int p[512];

    // Initialize the permutation vector
    static void initPerlin() {
        static bool initialized = false;
        if (initialized) return;
        for (int i = 0; i < 256; i++) p[256 + i] = p[i] = permutation[i];
        initialized = true;
    }

    static float fade(float t) {
        // 6t^5 - 15t^4 + 10t^3
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    static float lerp(float a, float b, float t) {
        return a + t * (b - a);
    }

    static float grad(int hash, float x, float y) {
        int h = hash & 7;
        float u = h < 4 ? x : y;
        float v = h < 4 ? y : x;
        return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
    }

    float WorldGenerator::perlinNoise(float x, float y) {
        initPerlin();

        int X = (int)floorf(x) & 255;
        int Y = (int)floorf(y) & 255;

        x -= floorf(x);
        y -= floorf(y);

        float u = fade(x);
        float v = fade(y);

        int aa = p[p[X] + Y];
        int ab = p[p[X] + Y + 1];
        int ba = p[p[X + 1] + Y];
        int bb = p[p[X + 1] + Y + 1];

        float res = lerp(
            lerp(grad(aa, x, y), grad(ba, x - 1, y), u),
            lerp(grad(ab, x, y - 1), grad(bb, x - 1, y - 1), u),
            v);
        return (res + 1.0f) / 2.0f; // Normalize to [0,1]
    }

    WorldGenerator::WorldGenerator(int width, int height, float noiseScale)
        : width(width), height(height), noiseScale(noiseScale), tiles(height, std::vector<TileType>(width, TileType::WATER)) {
        loadTileTextures();
    }

    void WorldGenerator::loadTileTextures() {
        tileTextures[(int)TileType::WATER] = LoadTexture(get_asset("water_tile").c_str());
        tileTextures[(int)TileType::DIRT] = LoadTexture(get_asset("dirt_tile").c_str());
        tileTextures[(int)TileType::GRASS] = LoadTexture(get_asset("grass_tile").c_str());
    }

    void WorldGenerator::generate() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                float noiseVal = perlinNoise(x * noiseScale, y * noiseScale);
                if (noiseVal < 0.3f) {
                    tiles[y][x] = TileType::WATER;
                }
                else if (noiseVal < 0.6f) {
                    tiles[y][x] = TileType::DIRT;
                }
                else {
                    tiles[y][x] = TileType::GRASS;
                }
            }
        }
    }

    void WorldGenerator::draw(const Vector2& cameraPos) {
        const int tileSize = 64; // assuming your tiles are 64x64 pixels

        int startX = (int)(cameraPos.x / tileSize);
        int startY = (int)(cameraPos.y / tileSize);
        int tilesX = 20; // number of tiles to draw horizontally (adjust to screen size)
        int tilesY = 15; // vertically

        for (int y = startY; y < startY + tilesY; y++) {
            for (int x = startX; x < startX + tilesX; x++) {
                if (x < 0 || y < 0 || x >= width || y >= height) continue;

                TileType type = tiles[y][x];
                Texture2D& tex = tileTextures[(int)type];
                DrawTexture(tex, x * tileSize - (int)cameraPos.x, y * tileSize - (int)cameraPos.y, WHITE);
            }
        }
    }

    TileType WorldGenerator::getTile(int x, int y) const {
        if (x < 0 || y < 0 || x >= width || y >= height) return TileType::WATER;
        return tiles[y][x];
    }

} // namespace Engine
