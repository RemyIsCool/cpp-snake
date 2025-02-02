#include "Apple.h"
#include "Snake.h"

class Game {
    std::shared_ptr<Snake> snake;
    Apple apple;
    int score;
    Texture2D snakeTexture;

    void resetGame();

public:
    Game();

    void update();
    void draw() const;
};
