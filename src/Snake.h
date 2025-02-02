#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"
#include <functional>
#include <queue>
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
    Texture2D texture;
    float frame;
    std::queue<int> keys;

    void extend();
    bool isOverlapping() const;
    float getTextureXCoord(int index) const;
    float getTextureRotation(int index) const;

public:
    std::vector<Vector2> body;
    bool dead;

    Snake(Vector2 spawn, int initialLength, Direction initialDirection, Vector2& applePosition,
          Texture2D texture);

    void update(std::function<void()> onEat);
    void draw() const;
};

#endif
