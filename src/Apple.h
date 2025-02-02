#include "Snake.h"
#include "raylib.h"
#include <memory>

class Apple {
    bool inSnake() const;

public:
    Vector2 position;
    std::shared_ptr<Snake> snake;

    Apple(const std::shared_ptr<Snake> snake);
    void place();
    void draw() const;
};
