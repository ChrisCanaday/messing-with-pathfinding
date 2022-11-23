#ifndef STATE_H
#define STATE_H

#include <vector>
#include <float.h>

typedef std::pair<double,double> priority;  // priority of the PQ
#define inf 999999999;                      // infinity


struct state{
  double g;                   // min true cost from start to cell
  double rhs;                 // min cost from previous cell (predecessor)

  int cost;                   // cost to move to (-1 if not allowed to go there)

  int i;                      // position on the board
  int j;                      // position on the board

  priority k;                 // [min(g,rhs) + h + k_m; min(g,rhs)]

  state();                    // constructor

  /* Comparison for main D* Lite driver */
  /* Checks if the i,j are the same     */
  bool operator != (const state &a) const;

  bool operator == (const state &a) const;
};

/* Comparison for the PQ Set */
struct comp{
  bool operator()(const state* s1, const state* s2) const;
};


#endif