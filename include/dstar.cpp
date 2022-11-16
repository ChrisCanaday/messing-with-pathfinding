#include "dstar.h"

// calculates h if needed then calculates k (priority)
priority Dstar::CalculateKey(state s){
  priority tmp;
  if(s.h == 0.0) s.h = CalculateHeuristic(s_start,s);
  tmp.first = std::min(s.g, s.rhs) + s.h + k_m;
  tmp.second = std::min(s.g, s.rhs);
  return tmp;
}

// psuedo code rn
void Dstar::UpdateVertex(state u){
  if(u.g != u.rhs /*&& u is in U*/){/*U.Update(u,CalculateKey(u))*/}
  else if(u.g != u.rhs /*&& u is not in U*/){/*U.Insert(u,CalculateKey(u))*/}
  else if(u.g == u.rhs /*&& u is in U*/){/*U.Remove(u)*/}
}

void Dstar::Initialize(){
  while(!U.Empty()) U.Pop();  // U = null
  k_m = 0;                    // k_m = 0

  // set all states rhs and g to DBL_MAX
  for(int i = 0; i < all_states.size(); i++){
    all_states[i].g = DBL_MAX;
    all_states[i].rhs = DBL_MAX;
  }
  s_goal.rhs = 0;             // rhs(s_goal) = 0
  //CalculateKey(s_goal);       // [h(s_start, s_goal); 0]
  U.Insert(s_goal,CalculateKey(s_goal));             // U.Insert(s_goal,[h(s_start, s_goal); 0])
}

// returns euclidean distance between node from and to
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