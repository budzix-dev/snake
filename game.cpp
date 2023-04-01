#include "game.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "constants.h"
#include "include/raylib.h"
#include "player.h"

namespace fs = std::filesystem;

Game::Game() { this->init(); }

void Game::init() {
    this->frames_counter = 0;
    this->game_over = false;
    this->can_change_direction = true;

    this->player = Player();

    this->generateFood();
}

void Game::generateFood() {
    Vector2 new_food_position;

    do {
        new_food_position.x = GetRandomValue(0, TILES_NUM - 1);
        new_food_position.y = GetRandomValue(0, TILES_NUM - 1);
    } while (this->player.occupiesTile(new_food_position));

    this->food_position = new_food_position;
}

void Game::draw() {
    if (!this->game_over) {
        this->drawGrid();
        this->drawFood();
        this->player.draw();
    } else {
        this->drawGameOver();
    }
}

void Game::drawGrid() {
    for (int i = 0; i < TILES_NUM; i++) {
        for (int j = 0; j < TILES_NUM; j++) {
            if ((i + j) % 2 == 0)
                DrawRectangle(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE,
                              TILE_SIZE, BG_COLOR1);
            else
                DrawRectangle(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE,
                              TILE_SIZE, BG_COLOR2);
        }
    }
}

void Game::drawFood() {
    DrawRectangle(this->food_position.x * TILE_SIZE,
                  this->food_position.y * TILE_SIZE, TILE_SIZE, TILE_SIZE,
                  FOOD_COLOR);
}

void Game::drawGameOver() {
    ClearBackground(BLACK);
    DrawText("Game Over!", 10, 20, 50, RED);
    DrawText("Press SPACE to play again", 10, 70, 40, WHITE);
}

bool Game::isValidPosition(Vector2 position) {
    return position.x >= 0 && position.x < TILES_NUM && position.y >= 0 &&
           position.y < TILES_NUM;
}

void Game::update() {
    if (!this->game_over) {
        if (this->frames_counter < FRAMES_BETWEEN_MOVEMENT)
            this->frames_counter++;
        else
            this->frames_counter = 0;

        if (this->can_change_direction) {
            Vector2 prev_direction = this->player.direction;
            if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) &&
                this->player.direction.x != -1)
                this->player.direction = {1, 0};
            else if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) &&
                     this->player.direction.x != 1)
                this->player.direction = {-1, 0};
            else if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) &&
                     this->player.direction.y != 1)
                this->player.direction = {0, -1};
            else if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) &&
                     this->player.direction.y != -1)
                this->player.direction = {0, 1};
            if (prev_direction.x != this->player.direction.x ||
                prev_direction.y != this->player.direction.y)
                this->can_change_direction = false;
        }

        if (this->frames_counter == 0) {
            Vector2 next_head_position = this->player.getNextHeadPosition();

            if ((this->game_over =
                     !this->isValidPosition(next_head_position) ||
                     (this->player.occupiesTile(next_head_position, false) &&
                      this->player.isMoving()))) {
                return;
            }

            if (next_head_position.x == this->food_position.x &&
                next_head_position.y == this->food_position.y) {
                this->player.grow();
                this->generateFood();
            }

            this->player.move();

            this->can_change_direction = true;
        }
    } else if (IsKeyPressed(KEY_SPACE)) {
        this->init();
    }

    BeginDrawing();
    this->draw();
    EndDrawing();
}
