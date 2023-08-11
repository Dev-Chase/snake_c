#include "settings.h"
#include "snake.h"

typedef enum { Start, Playing, Paused } GameState;

int main(void) {
  // Initializing Window
  InitWindow(W, H, "Snake in C!");
  SetTargetFPS(FPS);

  // Game Variables;
  char *title_text = "Press Space to Start";
  char *sub_title_text = "20";
  GameState game_state = Start;

  // Game Loop
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BG_COLOUR);
    if (game_state == Start) {
      DrawText(title_text, (W / 2) - MeasureText(title_text, FONT_SIZE) / 2,
               (H / 2) - (FONT_SIZE / 2), FONT_SIZE, FG_COLOUR);
      DrawText(sub_title_text,
               (W / 2) - MeasureText(sub_title_text, FONT_SIZE) / 2,
               (H / 2) - (FONT_SIZE / 2) + FONT_SIZE + 4, FONT_SIZE, FG_COLOUR);
      if (IsKeyPressed(KEY_SPACE)) {
        game_state = Playing;
      }
    } else if (game_state == Playing) {
      DrawText("Testing", 20, 20, FONT_SIZE, FG_COLOUR);

    } else {
      // Do Something
    }
    EndDrawing();
  }

  CloseWindow();
  return EXIT_SUCCESS;
}
