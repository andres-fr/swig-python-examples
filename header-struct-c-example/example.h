#ifndef EXAMPLE_H_
#define EXAMPLE_H_

#include <stdlib.h>

typedef struct pair {
  float x;
  float y;
} pair;

pair* CreatePair(float x, float y);

pair* AddPairs(const pair* p1, const pair* p2);

#endif // EXAMPLE_H_
