#include "state.h"

state::state(){
  g = inf;
  rhs = inf;
  i = -1;
  j = -1;
  k.first = inf;
  k.second = inf;
}

bool state::operator != (const state &a) const{
  return (i != a.i || j != a.j);
}

bool state::operator == (const state &a) const{
  return (i == a.i && j == a.j);
}

bool comp::operator()(const state* s1, const state* s2) const{
  return (s1->k < s2->k);
}