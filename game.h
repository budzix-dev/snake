#ifndef GAME_H
#define GAME_H

#include "include/raylib.h"
#include "player.h"

class Game {
   private:
    Vector2 food_position;
    int frames_counter;
    bool game_over;
    bool can_change_direction;

    void init();
    void draw();
    void generateFood();
    void drawGrid();
    void drawFood();
    void drawGameOver();
    bool isValidPosition(Vector2 position);

   public:
    Game();

    Player player;

    void update();
};

#endif