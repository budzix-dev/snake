#include <fstream>

#include "constants.h"
#include "game.h"
#include "include/raylib.h"

int main() {
    auto game = Game();

    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "Snake");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        game.update();
    }

    CloseWindow();

    return 0;
}