#include ""
#include <filesystem>
#include <vector>

using namespace std;
namespace fs = filesystem;

// Return the first asset file path that contains `name` in its filename
// Minimal Resource getter for Adernalin rush game.
string get_asset(const string& name, const AssetType& asset_type) {
    string default_path = "images";
    switch (asset_type) {
    case(AssetType::IMAGE):
        default_path = "images";
        break;
    case(AssetType::SOUND):
        default_path = "sounds";
        break;
    default:
        default_path = "images";
        break;
    };
    fs::path assets_path = fs::current_path() / "assets" / default_path;
    for (const auto& entry : fs::directory_iterator(assets_path)) {
        if (entry.is_regular_file()) {
            string filename = entry.path().filename().string();
            if (filename.find(name) != string::npos) { // name exists inside filename
                return entry.path().string(); // full path
            }
        }
    }
    return ""; // nothing found
}