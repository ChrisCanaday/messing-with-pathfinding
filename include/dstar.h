#ifndef DSTAR_H
#define DSTAR_H

#include <utility>
#include <queue>
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