#ifndef PQ_H
#define PQ_H

#include <vector>
#include <float.h>

struct state{
  double g = DBL_MAX;;        // min true cost from start to cell
  double rhs = DBL_MAX;       // min cost from cell to neighbor (best neighbor to potentially move to)
  double h = 0.0;             // heuristic (from start)

  int i;                      // position on the board
  int j;                      // position on the board

  std::pair<double,double> k; // this is the priority => [min(g,rhs) + h + k_m; min(g,rhs)]

  // comparison for priority queue
  bool operator > (const state &a) const{
    if(k.first > a.k.first) return true;
    else if(k.first < a.k.first) return false;
    return k.second > a.k.second;
  }
};

template <class T, class U>
class PQ{
  public:
    PQ();
    void Insert(T s, U k);
    void Update(T s, U k);
    state Top();
    U TopKey();
    void Remove(T s);
    bool Empty();


  private:
    int size;
};

#endif