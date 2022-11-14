#include "dstar.h"

std::pair<double,double> Dstar::CalculateKey(state s){
  return std::make_pair(s.k1,s.k2);
}

void Dstar::UpdateVertex(state u){
  if(u.g != u.rhs /*&& u is in U*/){/*U.Update(u,CalculateKey(u))*/}
  else if(u.g != u.rhs /*&& u is not in U*/){/*U.Insert(u,CalculateKey(u))*/}
  else if(u.g == u.rhs /*&& u is in U*/){/*U.Remove(u)*/}
}