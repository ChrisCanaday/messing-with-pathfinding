#ifndef DSTAR_H
#define DSTAR_H

#include "pqs.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <chrono>

class Dstar
{
public:
  priority CalculateKey(state *s);
  void Initialize(int height, int width);
  void UpdateVertex(state *u);
  void ComputeShortestPath();
  void Main(int height, int width);
  double CalculateHeuristic(const state *to, const state *from) const;
  void GetPredecessors(const state *u, std::vector<state *> &s);
  void GetSuccessors(const state *u, std::vector<state *> &s);
  bool IsOccupied(const int i, const int j) const;
  void JGRAPHPrintGrid();
  void PrintBox(int i, int j);
  // void SetStart();
  // void SetEnd();

//private:
  state *s_start, *s_goal, *s_last;
  bool changed;

  PQ U;
  std::vector<std::vector<state *> > grid;
  std::vector<state*> path;
  std::vector<state*> changed_edges;
};

#endif