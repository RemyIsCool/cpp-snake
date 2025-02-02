#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"
#include <functional>
#include <vector>

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
} Direction;

class Snake {
    Direction direction;
    Vector2& applePosition;

    void extend();
    bool isOverlapping();

public:
    std::vector<Vector2> body;
    bool dead;

    Snake(Vector2 spawn, int initialLength, Direction initialDirection, Vector2& applePosition);

    void update(std::function<void()> onEat);
    void draw() const;
};

#endif
