#include "Apple.h"
#include "Snake.h"

class Game {
    std::shared_ptr<Snake> snake;
    Apple apple;
    int score;

    void resetSnake();

public:
    Game();

    void update();
    void draw();
};
