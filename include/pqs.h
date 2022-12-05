#ifndef PQS_H
#define PQS_H

#include "state.h"
#include <set>
#include <iostream>

class PQ
{
public:
  void Insert(state *s, priority k);        // Inserts state s with priority k
  void Update(state *s, priority k);        // Updates state s in the PQ(new k)
  priority TopKey();                        // Returns the key of least priority
  void Remove(state *s);                    // Removes state s from the PQ
  bool Empty();                             // Returns if the PQ is empty
  void Print();                             // Prints the PQ (least to greatest)
  state *Top();                             // Returns the state with the least priority
  state *Pop();                             // Returns the state with the least prioirty
  bool Present(state *s);                   // Returns if the state s is in the PQ
  int GetSize();                            // Returns the size of the PQ
  void GetAllNodes(std::vector<state*> &v); // Puts all states in the PQ in v
  void Clear();
  int accesses = 0;

private:
  std::multiset<state *>::iterator it;      // iterator
  std::multiset<state *,comp> storage;      // PQ
};

#endif