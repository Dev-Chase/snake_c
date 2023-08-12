#ifndef SETTINGS_H
#define SETTINGS_H

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FPS 60
#define FONT_SIZE 28
#define TILE_SIZE 24
#define W TILE_SIZE * 20
#define H TILE_SIZE * 20
#define BG_COLOUR BLACK
#define FG_COLOUR WHITE
#define SNAKE_COLOUR GREEN
#define FOOD_COLOUR RED
#define BLOCK_SIZE                                                             \
  (Vector2) { TILE_SIZE, TILE_SIZE }
#define MOVE_SPEED 3
#define SCREEN_SHAKE_AMPLITUDE 3

#ifdef __cplusplus
}
#endif
#endif // !SETTINGS_H
