cmake_minimum_required(VERSION 3.15)
project(AdrenalinRush CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect all .cpp files
file(GLOB_RECURSE SOURCES
    "src/main.cpp"
    "src/engine/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    engine
    engine/animation
    missions
    "C:/vcpkg/installed/x64-mingw-dynamic/include"
)

# Link Raylib + required system libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    "C:/vcpkg/installed/x64-mingw-dynamic/lib/liblua.dll.a"
    "C:/vcpkg/installed/x64-mingw-dynamic/lib/libraylib.dll.a"
    "C:/vcpkg/installed/x64-mingw-dynamic/lib/libglfw3dll.a"
    winmm    # timeBeginPeriod
    gdi32    # Graphics Device Interface
    opengl32 # OpenGL
    shell32  # Sometimes required by Raylib
)

# Preprocessor definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE _CONSOLE)
