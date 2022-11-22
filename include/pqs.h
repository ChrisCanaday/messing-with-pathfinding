#ifndef PQS_H
#define PQS_H

#include "state.h"
#include <set>
#include <iostream>

class PQ
{
public:
  PQ();
  void Insert(state *s, std::pair<double, double> k);
  void Update(state *s, std::pair<double, double> k);
  priority TopKey();
  void Remove(state *s);
  bool Empty();
  void Print();
  state *Top();
  state *Pop();
  bool Present(state *s);
  int GetSize();
  void ReturnAllEntries(std::vector<state*> &v);

private:
  std::multiset<state *>::iterator it;
  std::multiset<state *,comp> storage;
  std::multiset<state *,comppos> present;
};

#endif