#include "player.h"

#include <algorithm>
#include <array>
#include <iterator>

#include "constants.h"
#include "include/raylib.h"

void Player::init(Vector2 initial_position = {0, 0}) {
    this->snake_tiles[0] = initial_position;
    this->length = 1;
}

Player::Player(Vector2 initial_position) { this->init(initial_position); }

Player::Player() { this->init(); };

void Player::draw() {
    for (int i = 0; i < this->length; i++) {
        DrawRectangle(this->snake_tiles[i].x * TILE_SIZE,
                      this->snake_tiles[i].y * TILE_SIZE, TILE_SIZE, TILE_SIZE,
                      PLAYER_COLOR);
    }
}

void Player::move() {
    Vector2 prev_tiles[TILES_NUM * TILES_NUM];
    std::copy(std::begin(this->snake_tiles), std::end(this->snake_tiles),
              std::begin(prev_tiles));

    this->snake_tiles[0].x += this->direction.x;
    this->snake_tiles[0].y += this->direction.y;

    for (int i = 1; i < this->length; i++) {
        this->snake_tiles[i] = prev_tiles[i - 1];
    }
}

bool Player::isMoving() const {
    return this->direction.x != 0 || this->direction.y != 0;
}

bool Player::occupiesTile(Vector2 tile, bool checkTail) const {
    int end = checkTail ? this->length : this->length - 1;

    for (int i = 0; i < end; i++) {
        if (this->snake_tiles[i].x == tile.x &&
            this->snake_tiles[i].y == tile.y)
            return true;
    }

    return false;
}

Vector2 Player::getNextHeadPosition() const {
    return {this->snake_tiles[0].x + this->direction.x,
            this->snake_tiles[0].y + this->direction.y};
}

void Player::grow() { this->length++; }

int Player::getLength() { return this->length; }