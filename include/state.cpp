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

  /*f(k.first == a.k.first) return (k.second > a.k.second);
  else return (k.first > a.k.first);*/
  return (k > a.k);
}

bool state::operator != (const state &a) const{
  return (i != a.i || j != a.j);
}

bool state::operator == (const state &a) const{
  return (i == a.i && j == a.j);
}