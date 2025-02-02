#include "Snake.h"
#include "common.h"
#include "raylib.h"
#include <functional>
#include <iostream>
#include <span>
#include <vector>

#define FRAME_COUNT 3.0f

Snake::Snake(Vector2 spawn, int initialLength, Direction initialDirection, Vector2& applePosition,
             Texture2D texture)
    : direction(initialDirection), applePosition(applePosition), texture(texture), body({spawn}) {
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

bool Snake::isOverlapping() const {
    Vector2 head = body.back();

    if (head.x < 0 || head.x >= (float)WIDTH / CELL_SIZE || head.y < 0 ||
        head.y >= (float)HEIGHT / CELL_SIZE) {
        return true;
    }

    for (Vector2 part : std::span<const Vector2>(body.begin(), body.end() - 1)) {
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

#define DIFF(var1, var2)                                                                           \
    { var1.x - var2.x, var1.y - var2.y }

float Snake::getTextureXCoord(int index) const {
    if (index <= 0 || index >= (int)body.size() - 1)
        return texture.width / FRAME_COUNT * 2;

    const Vector2 part = body.at(index);

    const Vector2 previous = body.at(index - 1);
    Vector2 diffPrevious = DIFF(part, previous);

    const Vector2 next = body.at(index + 1);
    Vector2 diffNext = DIFF(part, next);

    if (diffPrevious.x != diffNext.x && diffPrevious.y != diffNext.y) {
        return texture.width / FRAME_COUNT;
    }

    return 0;
}

float Snake::getTextureRotation(int index) const {
    const Vector2 part = body.at(index);

    if (index >= (int)body.size() - 1) {
        return direction == RIGHT ? 90 : direction == LEFT ? 270 : direction == DOWN ? 180 : 0;
    }

    if (index <= 0) {
        Vector2 diff = DIFF(part, body.at(index + 1));
        return diff.x == 0 ? (diff.y == 1 ? 180 : 0) : (diff.x == 1 ? 90 : 270);
    }

    const Vector2 previous = body.at(index - 1);
    Vector2 diffPrevious = DIFF(part, previous);

    const Vector2 next = body.at(index + 1);
    Vector2 diffNext = DIFF(part, next);

    if (previous.x == next.x) {
        return 0;
    }
    if (previous.y == next.y) {
        return 90;
    }

    const Vector2 sumPrevNext = {diffPrevious.x + diffNext.x, diffPrevious.y + diffNext.y};
    if (sumPrevNext.x == 1 && sumPrevNext.y == 1)
        return 180;
    if (sumPrevNext.x == 1 && sumPrevNext.y == -1)
        return 90;
    if (sumPrevNext.x == -1 && sumPrevNext.y == 1)
        return 270;
    return 0;
}

void Snake::draw() const {
    for (int i = 0; i < (int)body.size(); i++) {
        const Vector2 part = body.at(i);

        const float xCoord = getTextureXCoord(i);

        const Vector2 offset = {(float)texture.width / FRAME_COUNT / 2.0f *
                                    (CELL_SIZE / (texture.width / FRAME_COUNT)),
                                texture.height / 2.0f * (CELL_SIZE / (float)texture.height)};

        DrawTexturePro(
            texture, {xCoord, 0, texture.width / FRAME_COUNT, (float)texture.height},
            {part.x * CELL_SIZE + offset.x, part.y * CELL_SIZE + offset.y, CELL_SIZE, CELL_SIZE},
            offset, getTextureRotation(i), WHITE);
    }
}
