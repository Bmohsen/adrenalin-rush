#include "base.h"
#include <filesystem>
#include <vector>

using namespace std;
namespace fs = filesystem;

// Return the first asset file path that contains `name` in its filename
string get_asset(const string& name) {
    fs::path assets_path = fs::current_path() / "assets";

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