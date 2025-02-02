#include "Game.h"
#include "Snake.h"
#include "common.h"
#include "raylib.h"
#include <format>
#include <memory>

#define NEW_SNAKE

Game::Game() : apple(snake), score(0) {
    InitWindow(WIDTH, HEIGHT, "Snake");
    SetTargetFPS(10);
    snakeTexture = LoadTexture("assets/snake.png");
}

void Game::resetGame() {
    snake =
        std::make_shared<Snake>(Snake(Vector2{10, 10}, 10, RIGHT, apple.position, snakeTexture));
    apple.snake = snake;
    score = 0;
    apple.place();
}

void Game::update() {
    if (snake != nullptr && !snake->dead) {
        snake->update([this]() -> void {
            apple.place();
            score++;
        });
    } else {
        if (IsKeyPressed(KEY_ENTER)) {
            resetGame();
        }
    }
}

void Game::draw() const {
    BeginDrawing();
    ClearBackground(BLACK);

    if (snake && snake->dead) {
        DrawText("DEAD!", 500, 200, 100, RED);
        DrawText(std::format("You Scored: {}", score).c_str(), 540, 325, 30, WHITE);
        DrawText("Press Enter To Play Again", 480, 380, 25, GRAY);
    } else if (snake) {
        apple.draw();
        snake->draw();
        DrawText(std::format("Score: {}", score).c_str(), 10, 10, 25, GRAY);
    } else {
        DrawText("SNAKE", 470, 200, 100, GREEN);
        DrawText("Press Enter To Play", 510, 325, 25, WHITE);
    }

    EndDrawing();
}
