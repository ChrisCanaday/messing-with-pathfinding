#include <utility>
#include <float.h>

struct state{
  double g = DBL_MAX;;     // min true cost from start to cell
  double rhs = DBL_MAX;   // min cost from cell to neighbor (best neighbor to potentially move to)
  double h = 0.0;     // heuristic (from start)

  double k1 = 0.0;    // min(g,rhs) + h
  double k2 = 0.0;    // min(g,rhs)
};


class Dstar{
  std::pair<double,double> CalculateKey(state s);
  void Initialize();
  void UpdateVertex(state u);
  void Main();
  //void SetStart();
  //void SetEnd();

  state s_start, s_last, s_current;

};