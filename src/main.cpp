#include "Game.h"
#include "raylib.h"

int main() {
    Game game;

    while (!WindowShouldClose()) {
        game.update();
        game.draw();
    }

    CloseWindow();
}
