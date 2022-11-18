#ifndef PQ_H
#define PQ_H

#include "state.h"
#include <iostream>

class PQ{
  public:
    PQ();
    void Insert(state *s, std::pair<double,double> k);
    void Update(state *s, std::pair<double,double> k);
    priority TopKey();
    void Remove(state *s);
    bool Empty();
    void Print();
    state *Top();
    void Pop();
    bool Present(state *s);
    int GetSize();


  //private:
    void PercolateDown(int left, int right, state *s);
    void PercolateUp(state *s);

    int size;
    priority inf;
    std::vector<state*> heap;
};

#endif