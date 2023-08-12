#ifndef SNAKE_H
#define SNAKE_H
#include "settings.h"

#ifdef __cplusplus
extern "C" {
#endif

// Prototypes go here
typedef struct {
  Vector2 *body;
  Vector2 dir;
  uint16_t len_b; // Length of Body in sizeof(Vector2)
} Snake;

bool game_over(Snake *snake);
void move_snake(Snake *snake);
Rectangle get_rect(Vector2 pos);
void grow_snake(Snake *snake);
bool collides_snake(Snake *snake, Vector2 *block_pos);
void draw_snake(Snake *snake);

#ifdef __cplusplus
}
#endif

#endif // End first IFNDEF
