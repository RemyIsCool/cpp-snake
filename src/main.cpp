#include "Game.h"
#include "raylib.h"
#include <chrono>
#include <ctime>

int main() {
    Game game;

    while (!WindowShouldClose()) {
        game.update();
        game.draw();
    }

    CloseWindow();
}
