#ifndef STATE_H
#define STATE_H

#include <vector>
#include <float.h>

typedef std::pair<double,double> priority;  // priority of the PQ
#define inf 999999999.0;
//double infinity 999999999;


struct state{
  double g;                   // min true cost from start to cell
  double rhs;                 // min cost from previous cell (predecessor)
  double h;                   // heuristic (from start)

  int cost;                   // cost to move to (-1 if not allowed to go there)

  int i;                      // position on the board
  int j;                      // position on the board

  int id;                     // position in PQ

  priority k;                 // [min(g,rhs) + h + k_m; min(g,rhs)]

  state();

  // comparison for priority queue
  bool operator > (const state &a) const;
  bool operator < (const state &a) const;

  // comparison for main D* Lite driver
  bool operator != (const state &a) const;

  bool operator == (const state &a) const;

  bool operator () (state const* s1, state const* s2){
    return (s1->k < s2->k);
  }
};

struct comp{
  bool operator()(const state* s1, const state* s2) const;
  //bool operator==(const state* s1, const state* s2) const;
};

struct comppos{
  bool operator()(const state* s1, const state* s2) const;
};

#endif