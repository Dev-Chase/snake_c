#ifndef SNAKE_H
#define SNAKE_H
#include "settings.h"

#ifdef __cplusplus
extern "C" {
#endif

// Prototypes go here
typedef struct {
  Vector2 pos;
  Vector2 dir;
} BodyBlock;

typedef struct {
  BodyBlock *body;
  int len;
} Snake;

BodyBlock *new_body_block();

#ifdef __cplusplus
}
#endif

#endif // End first IFNDEF
