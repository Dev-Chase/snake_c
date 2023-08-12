#include "snake.h"
#include "raylib.h"
#include "raymath.h"
#include <string.h>

bool game_over(Snake *snake) {
  if ((snake->body->x + snake->dir.x < 0 ||
       snake->body->x + snake->dir.x + TILE_SIZE > W) ||
      (snake->body->y + snake->dir.y < 0 ||
       snake->body->y + snake->dir.y + TILE_SIZE > H)) {
    return true;
  }

  int i = 1 + (TILE_SIZE / MOVE_SPEED) * 3;
  while (snake->len_b > 1 + (TILE_SIZE / MOVE_SPEED) * 3 && i < snake->len_b) {
    if (CheckCollisionRecs(
            get_rect(Vector2Add(*snake->body,
                                (Vector2){.x = snake->dir.x * MOVE_SPEED,
                                          .y = snake->dir.y * MOVE_SPEED})),
            get_rect(snake->body[i]))) {
      return true;
    }
    i++;
  }
  return false;
}

void grow_snake(Snake *snake) {
  snake->body = realloc(snake->body, (snake->len_b + TILE_SIZE / MOVE_SPEED) *
                                         sizeof(Vector2));
  for (int i = 0; i < TILE_SIZE / MOVE_SPEED; i++) {
    snake->body[snake->len_b + i] = snake->body[snake->len_b - 1];
  }
  snake->len_b += TILE_SIZE / MOVE_SPEED;
}

void move_snake(Snake *snake) {
  for (int i = snake->len_b - 1; i > 0; i--) {
    snake->body[i] = snake->body[i - 1];
  }
  snake->body->x += snake->dir.x * MOVE_SPEED;
  snake->body->y += snake->dir.y * MOVE_SPEED;
}

Rectangle get_rect(Vector2 pos) {
  return (Rectangle){pos.x, pos.y, TILE_SIZE, TILE_SIZE};
}

bool collides_snake(Snake *snake, Vector2 *block_pos) {
  for (int i = 0; i < snake->len_b; i++) {
    if (CheckCollisionRecs(get_rect(*block_pos), get_rect(snake->body[i]))) {
      return true;
    }
  }
  return false;
}

void draw_snake(Snake *snake) {
  for (int i = 0; i < snake->len_b; i++) {
    DrawRectangleV(snake->body[i], BLOCK_SIZE, SNAKE_COLOUR);
  }
}
