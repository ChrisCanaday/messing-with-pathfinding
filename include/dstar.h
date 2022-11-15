#ifndef DSTAR_H
#define DSTAR_H

#include <utility>
#include <queue>
#include <vector>
#include "priorityq.h"

class Dstar{
public:
  void CalculateKey(state s);
  void Initialize();
  void UpdateVertex(state u);
  void ComputeShortestPath();
  void Main();
  double CalculateHeuristic(const state &to, const state &from) const;
  //void SetStart();
  //void SetEnd();

  state s_start, s_goal, s_current;
  double k_m;

  std::priority_queue<state, std::vector<state>, std::greater<state>> U;

  std::vector<state> all_states;
};

#endif