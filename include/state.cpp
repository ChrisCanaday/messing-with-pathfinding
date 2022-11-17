#include "state.h"

state::state(){
  g = DBL_MAX;
  rhs = DBL_MAX;
  h = 0.0;
  i = -1;
  j = -1;
  id = -1;
  k.first = DBL_MAX;
  k.second = DBL_MAX;
}

bool state::operator > (const state &a) const{
  if(k.first-0.001 > a.k.first) return true;
  else if(k.first < a.k.first-0.001) return false;
  return k.second > a.k.second;
}

bool state::operator != (const state &a) const{
  return (i != a.i || j != a.j);
}

bool state::operator == (const state &a) const{
  return (i == a.i && j == a.j);
}