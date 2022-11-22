#include "state.h"

state::state(){
  g = inf;
  rhs = inf;
  h = 0.0;
  i = -1;
  j = -1;
  id = -1;
  k.first = inf;
  k.second = inf;
}

bool state::operator > (const state &a) const{

  /*f(k.first == a.k.first) return (k.second > a.k.second);
  else return (k.first > a.k.first);*/
  return (k > a.k);
}

bool state::operator < (const state &a) const{
  return (k < a.k);
}

bool state::operator != (const state &a) const{
  return (i != a.i || j != a.j);
  //return (k != a.k);
}

bool state::operator == (const state &a) const{
  return (i == a.i && j == a.j);
  //return (k == a.k);
}

bool comp::operator()(const state* s1, const state* s2) const{
  return (s1->k < s2->k);
}

bool comppos::operator()(const state* s1, const state* s2) const{
  std::pair<int,int> s1p, s2p;
  s1p.first = s1->i;
  s1p.second = s1->j;
  s2p.first = s2->i;
  s2p.second = s2->j;

  return (s1p < s2p);
}