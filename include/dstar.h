#ifndef DSTAR_H
#define DSTAR_H

#include "priorityq.h"
#include <algorithm>
#include <cmath>

class Dstar{
  public:
    priority CalculateKey(state &s);
    void Initialize();
    void UpdateVertex(state &u);
    void ComputeShortestPath();
    void Main();
    double CalculateHeuristic(const state &to, const state &from) const;
    void GetPredecessors(state &u, std::vector<state> &s);
    void GetSuccessors(state &u, std::vector<state> &s);
    bool IsOccupied(int i, int j);
    void MakePath();
    bool InBounds(int i, int j);
    //void SetStart();
    //void SetEnd();

    state *s_start, *s_goal, *s_last;
    double k_m;
    bool changed;

    PQ U;

    std::vector<state> all_states;
    std::vector<std::vector<state> > grid;
    std::vector<state> path;
    std::vector<state> changed_edges;
};

#endif