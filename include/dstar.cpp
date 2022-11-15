#include "dstar.h"
#include <algorithm>
#include <cmath>

// calculates h if needed then calculates k (priority)
void Dstar::CalculateKey(state s){
  if(s.h == 0.0) s.h = CalculateHeuristic(s_start,s);
  s.k.first = std::min(s.g, s.rhs) + s.h + k_m;
  s.k.second = std::min(s.g, s.rhs);
}

// psuedo code rn
void Dstar::UpdateVertex(state u){
  if(u.g != u.rhs /*&& u is in U*/){/*U.Update(u,CalculateKey(u))*/}
  else if(u.g != u.rhs /*&& u is not in U*/){/*U.Insert(u,CalculateKey(u))*/}
  else if(u.g == u.rhs /*&& u is in U*/){/*U.Remove(u)*/}
}

void Dstar::Initialize(){
  while(!U.empty()) U.pop();  // U = null
  k_m = 0;                    // k_m = 0

  // set all states rhs and g to DBL_MAX
  for(int i = 0; i < all_states.size(); i++){
    all_states[i].g = DBL_MAX;
    all_states[i].rhs = DBL_MAX;
  }
  s_goal.rhs = 0;             // rhs(s_goal) = 0
  CalculateKey(s_goal);       // [h(s_start, s_goal); 0]
  U.push(s_goal);             // U.Insert(s_goal)
}

// euclidean distance
double Dstar::CalculateHeuristic(const state &to, const state &from) const{
  int di = abs(from.i - to.i);
  int dj = abs(from.j - to.j);

  return sqrt(di*di + dj*dj);
}

void Dstar::ComputeShortestPath(){
  // do stuff
}

void Dstar::Main(){
  // do stuff
}