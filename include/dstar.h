#ifndef DSTAR_H
#define DSTAR_H

#include "priorityq.h"
#include <algorithm>
#include <cmath>

class Dstar{
  public:
    priority CalculateKey(state s);
    void Initialize();
    void UpdateVertex(state u);
    void ComputeShortestPath();
    void Main();
    double CalculateHeuristic(const state &to, const state &from) const;
    //void SetStart();
    //void SetEnd();

    state s_start, s_goal, s_current;
    double k_m;

    PQ U;

    std::vector<state> all_states;
};

#endif