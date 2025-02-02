#include "Snake.h"
#include "common.h"
#include <functional>
#include <span>
#include <vector>

Snake::Snake(Vector2 spawn, int initialLength, Direction initialDirection, Vector2& applePosition)
    : direction(initialDirection), applePosition(applePosition) {
    body = {spawn};

    for (int i = 0; i < initialLength - 1; i++) {
        extend();
    }
}

void Snake::extend() {
    Vector2 back = body.back();

#define PUSH(dir, xChange, yChange)                                                                \
    case dir:                                                                                      \
        body.push_back(Vector2{back.x xChange, back.y yChange});                                   \
        break;

    switch (direction) {
        PUSH(UP, , -1)
        PUSH(DOWN, , +1)
        PUSH(LEFT, -1, )
        PUSH(RIGHT, +1, )
    }

#undef PUSH
}

bool Snake::isOverlapping() {
    Vector2 head = body.back();

    if (head.x < 0 || head.x >= (float)WIDTH / CELL_SIZE || head.y < 0 ||
        head.y >= (float)HEIGHT / CELL_SIZE) {
        return true;
    }

    for (Vector2 part : std::span<Vector2>(body.begin(), body.end() - 1)) {
        if (head.x == part.x && head.y == part.y) {
            return true;
        }
    }

    return false;
}

void Snake::update(std::function<void()> onEat) {
#define MOVE(dir, op)                                                                              \
    case KEY_##dir:                                                                                \
        if (direction != op)                                                                       \
            direction = dir;                                                                       \
        break;

#define MOVES(a, b) MOVE(a, b) MOVE(b, a)

    switch (GetKeyPressed()) {
        MOVES(UP, DOWN);
        MOVES(LEFT, RIGHT);
    }

#undef MOVES
#undef MOVE

    Vector2 head = body.back();
    if (head.x == applePosition.x && head.y == applePosition.y) {
        onEat();
    } else {
        body.erase(body.begin());
    }
    extend();

    if (isOverlapping()) {
        dead = true;
    }
}

void Snake::draw() const {
    for (Vector2 part : body) {
        DrawRectangle(part.x * CELL_SIZE, part.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, GREEN);
    }
}
