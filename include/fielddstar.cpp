#include "fielddstar.h"

/* Calculates the key (priority) of the state s */
priority FDstar::CalculateKey(state *s)
{
  priority ans;

  ans.first = std::min(s->g, s->rhs) + CalculateHeuristic(s_start, s);
  ans.second = std::min(s->g, s->rhs);

  return ans; // [min(s->g,s->rhs) + s->h; min(s->g,s->rhs)]
};

/* Initializes the Dstar class*/
void FDstar::Initialize()
{
  std::vector<state *> tmp;
  state *s;

  U.Clear(); // U = NULL

  // init grid
  for (int i = 0; i < 5; i++){
    tmp.clear();
    for (int j = 0; j < 3; j++){
      s = new state;
      if ((i == 2 || i == 1 || i == 3 /*|| i == 4*/) && j == 1){
        s->cost = -1;
      }else{
        s->cost = 1;
      }

      s->i = i;
      s->j = j;
      tmp.push_back(s);
    }
    grid.push_back(tmp);
  }

  // print original board state
  for (size_t i = 0; i < grid.size(); i++){
    for (size_t j = 0; j < grid[0].size(); j++){
      printf("%lu:%lu ", i, j);
      std::cout << grid[i][j]->k.first << "|" << grid[i][j]->k.second << std::endl;
    }
  }

  // set start and goal
  s_start = grid[1][0];
  s_goal = grid[4][2];

  // setup PQ
  s_goal->rhs = 0;
  U.Insert(s_goal, CalculateKey(s_goal));
};

/* Updates state u in the PQ */
void FDstar::UpdateVertex(state *u)
{
  //std::vector<state *> tmp;
  std::vector<std::pair<state*,state*> > tmp;
  double tmprhs = inf;

  // if not goal set rhs
  if (*u != *s_goal){
    //GetSuccessors(u, tmp);
    GetConnbrs(u,tmp);

    for (size_t i = 0; i < tmp.size(); i++){
      tmprhs = std::min(tmprhs, ComputeCost(u,tmp[i].first,tmp[i].second));
    }
    u->rhs = tmprhs;
  }

  // if in the PQ remove it
  if (U.Present(u)) U.Remove(u);

  // if locally inconsistent then add to the PQ
  if (u->rhs != u->g) U.Insert(u, CalculateKey(u));
};

/* LPA* */
void FDstar::ComputeShortestPath()
{
  state *u;
  std::vector<state *> tmp;
  size_t i;

  while (U.TopKey() < CalculateKey(s_start) || s_start->rhs != s_start->g){
    u = U.Pop();

    // if overly consistent make it locally consistent
    // then update all predecessors
    if (u->g > u->rhs){
      u->g = u->rhs;
      GetPredecessors(u, tmp);
      for (i = 0; i < tmp.size(); i++){
        UpdateVertex(tmp[i]);
      }
    }else{

      // set estimated distance to finish to infinity
      // them update all predecessors and self
      u->g = inf;
      GetPredecessors(u, tmp);
      tmp.push_back(u);
      for (i = 0; i < tmp.size(); i++){
        UpdateVertex(tmp[i]);
      }
    }
  }
};

/* Main D* Lite Driver */
void FDstar::Main()
{
  std::vector<state *> tmp;
  state *tmpstate;
  double min, oldmin, halt;
  size_t i;

  halt = inf;

  // init, make initial run, start path
  Initialize();
  ComputeShortestPath();
  path.push_back(s_start);

  // test change
  changed = true;
  GetSuccessors(grid[4][1], tmp);
  grid[4][1]->cost = -1;
  for (size_t i = 0; i < tmp.size(); i++) changed_edges.push_back(tmp[i]);

  // the loop to progress from start to finish
  while (s_start != s_goal){

    // return if no path
    if (s_start->g == halt) return;

    // Calculate the next step
    GetSuccessors(s_start, tmp);

    min = inf;
    oldmin = min;
    for (i = 0; i < tmp.size(); i++){
      min = std::min(min, CalculateHeuristic(s_start, tmp[i]) + tmp[i]->g);
      if (min != oldmin){
        tmpstate = tmp[i];
        oldmin = min;
      }
    }

    // set start to the next step and add it to the path
    s_start = tmpstate;
    path.push_back(s_start);

    // move robot to start

    // check for changes

    if (changed){

      // update all of the changed nodes
      for (i = 0; i < changed_edges.size(); i++){
        UpdateVertex(changed_edges[i]);
      }

      // update every node in the PQ
      U.GetAllNodes(tmp);

      for (i = 0; i < tmp.size(); i++){
        U.Update(tmp[i], CalculateKey(tmp[i]));
      }

      // recompute the path
      ComputeShortestPath();
      changed = false;
    }
  }
};

/* Calculates the cost from one node to another. Uses Euclidean Distance */
double FDstar::CalculateHeuristic(const state *to, const state *from) const
{
  if(to->cost < 0 || from->cost < 0) return inf;
  double di = abs(to->i - from->i);
  double dj = abs(to->j - from->j);

  return sqrt(di * di + dj * dj);
};

/* Returns all adjacent nodes that are legal */
void FDstar::GetPredecessors(const state *u, std::vector<state *> &s)
{
  s.clear();

  // check every cell around the current cell
  if (!IsOccupied(u->i + 1, u->j)) s.push_back(grid[u->i + 1][u->j]);
  if (!IsOccupied(u->i + 1, u->j + 1)) s.push_back(grid[u->i + 1][u->j + 1]);
  if (!IsOccupied(u->i, u->j + 1)) s.push_back(grid[u->i][u->j + 1]);
  if (!IsOccupied(u->i - 1, u->j + 1)) s.push_back(grid[u->i - 1][u->j + 1]);
  if (!IsOccupied(u->i - 1, u->j)) s.push_back(grid[u->i - 1][u->j]);
  if (!IsOccupied(u->i - 1, u->j - 1)) s.push_back(grid[u->i - 1][u->j - 1]);
  if (!IsOccupied(u->i, u->j - 1)) s.push_back(grid[u->i][u->j - 1]);
  if (!IsOccupied(u->i + 1, u->j - 1)) s.push_back(grid[u->i + 1][u->j - 1]);
};

/* Returns all adjacent nodes that are legal */
void FDstar::GetSuccessors(const state *u, std::vector<state *> &s)
{
  s.clear();

  // check every cell around the current cell
  if (!IsOccupied(u->i + 1, u->j)) s.push_back(grid[u->i + 1][u->j]);
  if (!IsOccupied(u->i + 1, u->j + 1)) s.push_back(grid[u->i + 1][u->j + 1]);
  if (!IsOccupied(u->i, u->j + 1)) s.push_back(grid[u->i][u->j + 1]);
  if (!IsOccupied(u->i - 1, u->j + 1)) s.push_back(grid[u->i - 1][u->j + 1]);
  if (!IsOccupied(u->i - 1, u->j)) s.push_back(grid[u->i - 1][u->j]);
  if (!IsOccupied(u->i - 1, u->j - 1)) s.push_back(grid[u->i - 1][u->j - 1]);
  if (!IsOccupied(u->i, u->j - 1)) s.push_back(grid[u->i][u->j - 1]);
  if (!IsOccupied(u->i + 1, u->j - 1)) s.push_back(grid[u->i + 1][u->j - 1]);
};

/* Returns if the cell at i,j is untraversable */
bool FDstar::IsOccupied(const int i, const int j) const
{
  // check to see if you are outside of the grid
  if (i >= (int)grid.size() || i < 0) return true;
  if (j >= (int)grid[0].size() || j < 0) return true;
  
  // return if the node is a wall
  return (grid[i][j]->cost < 0);
};

double FDstar::ComputeCost(state *s, state *s_a, state *s_b){
    state *s1, *s2;
    double c, b, v_s, f, x, y, comp;
    comp = inf;

    if(CalculateHeuristic(s_a,s) != 1){
        s1 = s_b;
        s2 = s_a;
    }else{
        s1 = s_a;
        s2 = s_b;
    }

    c = CalculateHeuristic(s,s1) + CalculateHeuristic(s1,s2);
    b = CalculateHeuristic(s,s1);

    if(std::min(c,b) == comp){
        v_s = std::min(c,b) + s1->g;
    }else{
        f = s1->g - s2->g;

        if(f <= b){
            if(c <- f){
                v_s = c*sqrt(2) + s2->g;
            }else{
                y = std::min(f/(sqrt(c*c-f*f)),(double) 1);
                v_s = c*sqrt(1+y*y) + f*(1-y) + s2->g;
            }
        }else{
            if(c <= b){
                v_s = c*sqrt(2) + s2->g;
            }else{
                x = 1-std::min(b/(sqrt(c*c-b*b)),(double) 1);
                v_s = c*sqrt(1+(1-x)*(1-x)) + b*x + s2->g;
            }
        }
    }

    return v_s;
}

void FDstar::GetConnbrs(state *s, std::vector<std::pair<state*,state*> > &v){
    std::pair<state*,state*> tmp;
    v.clear();

    tmp.first = grid[s->i+1][s->j-1];
    tmp.second = grid[s->i+1][s->j];
    v.push_back(tmp);
    tmp.first = tmp.second;
    tmp.second = grid[s->i+1][s->j+1];
    v.push_back(tmp);
    tmp.first = tmp.second;
    tmp.second = grid[s->i][s->j+1];
    v.push_back(tmp);
    tmp.first = tmp.second;
    tmp.second = grid[s->i-1][s->j+1];
    v.push_back(tmp);
    tmp.first = tmp.second;
    tmp.second = grid[s->i-1][s->j];
    v.push_back(tmp);
    tmp.first = tmp.second;
    tmp.second = grid[s->i-1][s->j-1];
    v.push_back(tmp);
    tmp.first = tmp.second;
    tmp.second = grid[s->i][s->j-1];
    v.push_back(tmp);
    tmp.first = tmp.second;
    tmp.second = grid[s->i+1][s->j-1];
    v.push_back(tmp);
}