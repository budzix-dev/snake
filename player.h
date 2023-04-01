#ifndef PLAYER_H
#define PLAYER_H

#include "constants.h"
#include "include/raylib.h"

class Player {
   private:
    int length = 1;
    Vector2 snake_tiles[TILES_NUM * TILES_NUM] = {{0, 0}};
    void init(Vector2 initial_position);

   public:
    Player(Vector2 initial_position);
    Player();

    Vector2 direction = {0, 0};

    void move();
    void draw();
    bool occupiesTile(Vector2 tile, bool checkTail = true) const;
    bool isMoving() const;
    Vector2 getNextHeadPosition() const;
    void grow();
    int getLength();
};

#endif