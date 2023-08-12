#include "raylib.h"
#include "settings.h"
#include "snake.h"

typedef enum { Menu, Playing } GameState;

void random_pos(Snake *snake, Vector2 *block) {
  do {
    block->x = rand() % (W - TILE_SIZE + 1);
    block->y = rand() % (H - TILE_SIZE + 1);
  } while (collides_snake(snake, block));
}

int main(void) {
  // Initializing Window & Camera
  InitWindow(W, H, "Snake in C!");
  SetTargetFPS(FPS);
  Camera2D camera = {.offset = (Vector2){0, 0},
                     .target = (Vector2){0, 0},
                     .zoom = 1.,
                     .rotation = 0.};
  int screenshake = 0;

  // Seeding RNG
  srand(time(NULL));

  // Game Variables;
  GameState game_state = Menu;
  bool is_paused = false;

  char title_text[25] = "Press Space to Start";
  char sub_title_text[25] = "";

  uint16_t score;
  char *score_text;
  bool show_score = false;

  Snake snake = {
      .body = malloc(sizeof(Vector2)),
      .len_b = 1,
  };
  Vector2 food;

  // Game Loop
  while (!WindowShouldClose()) {
    BeginDrawing();
    BeginMode2D(camera);
    ClearBackground(BG_COLOUR);
    if (screenshake) {
      camera.target.x =
          rand() % SCREEN_SHAKE_AMPLITUDE * 2 - SCREEN_SHAKE_AMPLITUDE / 2.;
      camera.target.y =
          rand() % SCREEN_SHAKE_AMPLITUDE * 2 - SCREEN_SHAKE_AMPLITUDE / 2.;
      screenshake--;
      if (!screenshake) {
        camera.target.x = 0;
        camera.target.y = 0;
      }
    }

    switch (game_state) {
    case Menu:
      DrawText(title_text, (W / 2) - MeasureText(title_text, FONT_SIZE) / 2,
               (H / 2) - (FONT_SIZE / 2), FONT_SIZE, FG_COLOUR);
      DrawText(sub_title_text,
               (W / 2) - MeasureText(sub_title_text, FONT_SIZE) / 2,
               (H / 2) - (FONT_SIZE / 2) - FONT_SIZE - 4, FONT_SIZE, FG_COLOUR);
      if (IsKeyPressed(KEY_SPACE)) {
        game_state = Playing;
        show_score = true;

        // Initialize New Game if not in Paused State
        if (!is_paused) {
          score = 0;
          asprintf(&score_text, "Score: %d", score);
          if (snake.len_b > 1) {
            snake.body = realloc(snake.body, 1);
            snake.len_b = 1;
          }
          *snake.body = (Vector2){(int)(W / TILE_SIZE / 2) * TILE_SIZE,
                                  (int)(H / TILE_SIZE / 2) * TILE_SIZE};
          snake.dir = (Vector2){.x = 1., .y = 0.};
          random_pos(&snake, &food);
        }
        is_paused = false;
      }
      break;
    case Playing:
      // Updating Sprites
      if (IsKeyDown(KEY_RIGHT) ^ IsKeyDown(KEY_LEFT) && !snake.dir.x &&
          (int)snake.body->y % TILE_SIZE == 0) {
        snake.dir.x = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);
        snake.dir.y = 0;
      } else if (IsKeyDown(KEY_UP) ^ IsKeyDown(KEY_DOWN) && !snake.dir.y &&
                 (int)snake.body->x % TILE_SIZE == 0) {
        snake.dir.y = IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP);
        snake.dir.x = 0;
      }
      // Game Over Checks
      if (!game_over(&snake))
        move_snake(&snake);
      else {
        // Seeding RNG
        srand(time(NULL));
        screenshake = FPS / 6;
        show_score = true;
        game_state = Menu;
        strncpy(sub_title_text, "Game Over.", 25);
        strncpy(title_text, "Press Space to Restart", 25);
        EndDrawing();
        continue;
      }
      if (collides_snake(&snake, &food)) {
        score++;
        asprintf(&score_text, "Score: %d", score);
        grow_snake(&snake);
        do {
          random_pos(&snake, &food);
        } while (collides_snake(&snake, &food));
      }

      // Drawing Sprites
      DrawRectangleV(food, BLOCK_SIZE, FOOD_COLOUR);
      draw_snake(&snake);

      // Pause Checks
      if (IsKeyPressed(KEY_SPACE)) {
        game_state = Menu;
        is_paused = true;
        strncpy(sub_title_text, "Game Paused", 25);
        strncpy(title_text, "Press Space to Unpause", 25);
        EndDrawing();
        continue;
      }
      break;
    };
    if (show_score)
      DrawText(score_text, 10, 10, FONT_SIZE - 4, FG_COLOUR);
    EndMode2D();
    EndDrawing();
  }

  free(snake.body);
  free(score_text);
  CloseWindow();
  return EXIT_SUCCESS;
}
