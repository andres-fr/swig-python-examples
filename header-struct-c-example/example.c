#include "example.h"

pair* CreatePair(float x, float y){
  pair* result = (pair*)malloc(sizeof(pair));
  result->x = x;
  result->y = y;
  return result;
};

pair* AddPairs(const pair* p1, const pair* p2){
  pair* result = (pair*)malloc(sizeof(pair));
  result->x = p1->x + p2->x;
  result->y = p1->y + p2->y;
  return result;
}
