#include "Snake.h"
#include "raylib.h"
#include <memory>

class Apple {
    std::shared_ptr<Snake> snake;

    bool inSnake();

public:
    Vector2 position;

    Apple(std::shared_ptr<Snake> snake);
    void place();
    void draw();
};
