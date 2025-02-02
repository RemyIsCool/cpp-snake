#include "Apple.h"
#include "common.h"
#include "raylib.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Apple::Apple(const std::shared_ptr<Snake> snake) : snake(snake) {
    std::srand(std::time(0));

    place();
}

void Apple::draw() const {
    DrawRectangle(position.x * CELL_SIZE, position.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);
}

bool Apple::inSnake() const {
    if (snake == nullptr) {
        std::cout << "here" << std::endl;
        return false;
    }

    for (const Vector2 part : snake->body) {
        if (part.x == position.x && part.y == position.y)
            return true;
    }

    return false;
}

void Apple::place() {
#define RANDOM(dim) (float)(std::rand() % dim / CELL_SIZE)
    do {
        position = {RANDOM(WIDTH), RANDOM(HEIGHT)}; // NOLINT
    } while (inSnake());
}
