#include "dstar.h"

priority Dstar::CalculateKey(state *s){
    priority ans;
    ans.first = std::min(s->g, s->rhs) + CalculateHeuristic(s_start,s);
    ans.second = std::min(s->g,s->rhs);

    return ans;
};

void Dstar::Initialize(){
    std::vector<state*> tmp;
    state *s;


    while(!U.Empty()) U.Pop();  // U = NULL

    for(int i = 0; i < 5; i++){
    tmp.clear();
    for(int j = 0; j < 3; j++){
      s = new state;
      if((i == 2 || i == 1 || i == 3 /*|| i == 4*/) && j == 1){
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

    for(size_t i = 0; i < grid.size(); i++){
        for(size_t j = 0; j < grid[0].size(); j++){
            printf("%d:%d ",i,j);
            std::cout << grid[i][j]->k.first << "|" << grid[i][j]->k.second << std::endl;
        }
    }

    s_start = grid[1][0];

    s_goal = grid[4][2];
    s_goal->rhs = 0;
    U.Insert(s_goal,CalculateKey(s_goal));
};
void Dstar::UpdateVertex(state *u){
    std::vector<state*> tmp;
    double tmprhs = inf;

    if(*u != *s_goal){
        GetSuccessors(u,tmp);

        for(size_t i = 0; i < tmp.size(); i++){
            tmprhs = std::min(tmprhs,CalculateHeuristic(tmp[i],u) + tmp[i]->g);
        }
        u->rhs = tmprhs;
    }

    if(U.Present(u)) U.Remove(u);

    if(u->rhs != u->g) U.Insert(u,CalculateKey(u));
};
void Dstar::ComputeShortestPath(){
    state *u;
    std::vector<state*> tmp;
    size_t i;

    while(U.TopKey() < CalculateKey(s_start) || s_start->rhs != s_start->g){
        u = U.Pop();

        if(u->g > u->rhs){
            u->g = u->rhs;
            GetPredecessors(u,tmp);
            for(i = 0; i < tmp.size(); i++){
                UpdateVertex(tmp[i]);
            }
        }else{
            u->g = inf;
            GetPredecessors(u,tmp);
            tmp.push_back(u);
            for(i = 0; i < tmp.size(); i++){
                UpdateVertex(tmp[i]);
            }
        }
    }
};
void Dstar::Main(){
    std::vector<state*> tmp;
    state *tmpstate;
    double min, oldmin, halt;
    size_t i;

    halt = inf;

    Initialize();
    ComputeShortestPath();
    path.push_back(s_start);

    changed = true;
    GetSuccessors(grid[4][1],tmp);
    grid[4][1]->cost = -1;
    for(size_t i = 0; i < tmp.size(); i++) changed_edges.push_back(tmp[i]);

    while(s_start != s_goal){
        if(s_start->g == halt) return;

        GetSuccessors(s_start,tmp);

        min = inf;
        oldmin = min;
        for(i = 0; i < tmp.size(); i++){
            min = std::min(min,CalculateHeuristic(s_start,tmp[i]) + tmp[i]->g);
            if(min != oldmin){
                tmpstate = tmp[i];
                oldmin = min;
            }
        }
        s_start = tmpstate;
        path.push_back(s_start);

        // move robot to start

        // check for changes

        if(changed){

            for(i = 0; i < changed_edges.size(); i++){
                UpdateVertex(changed_edges[i]);
            }

            U.ReturnAllEntries(tmp);

            for(i = 0; i < tmp.size(); i++){
                U.Update(tmp[i],CalculateKey(tmp[i]));
            }
            ComputeShortestPath();
            changed = false;
            // for all changed edges
            //   update edge costs
            //   UpdateVertex
            // for all state in PQ
            //   Update(s,key(s))
            // computeshortestpath
        }
    }
};
double Dstar::CalculateHeuristic(const state *to, const state *from) const{
  double di = abs(to->i - from->i);
  double dj = abs(to->j - from->j);

  return sqrt(di*di+dj*dj);
};
void Dstar::GetPredecessors(state *u, std::vector<state *> &s){
  s.clear();
  //u.k.first = -1;
  //u.k.second = -1;

  // check every block around us
  //printf("before block\n");
  if(!IsOccupied(u->i+1,u->j))   s.push_back(grid[u->i+1][u->j]);
  if(!IsOccupied(u->i+1,u->j+1)) s.push_back(grid[u->i+1][u->j+1]);
  if(!IsOccupied(u->i,u->j+1))   s.push_back(grid[u->i][u->j+1]);
  if(!IsOccupied(u->i-1,u->j+1)) s.push_back(grid[u->i-1][u->j+1]);
  if(!IsOccupied(u->i-1,u->j))   s.push_back(grid[u->i-1][u->j]);
  if(!IsOccupied(u->i-1,u->j-1)) s.push_back(grid[u->i-1][u->j-1]);
  if(!IsOccupied(u->i,u->j-1))   s.push_back(grid[u->i][u->j-1]);
  if(!IsOccupied(u->i+1,u->j-1)) s.push_back(grid[u->i+1][u->j-1]);
};
void Dstar::GetSuccessors(state *u, std::vector<state *> &s){
  s.clear();
  
  if(IsOccupied(u->i,u->j)) return;

  if(InBounds(u->i+1,u->j) && !IsOccupied(u->i+1,u->j)) s.push_back(grid[u->i+1][u->j]);
  if(InBounds(u->i+1,u->j+1) && !IsOccupied(u->i+1,u->j+1)) s.push_back(grid[u->i+1][u->j+1]);
  if(InBounds(u->i,u->j+1) && !IsOccupied(u->i,u->j+1)) s.push_back(grid[u->i][u->j+1]);
  if(InBounds(u->i-1,u->j+1) && !IsOccupied(u->i-1,u->j+1)) s.push_back(grid[u->i-1][u->j+1]);
  if(InBounds(u->i-1,u->j) && !IsOccupied(u->i-1,u->j)) s.push_back(grid[u->i-1][u->j]);
  if(InBounds(u->i-1,u->j-1) && !IsOccupied(u->i-1,u->j-1)) s.push_back(grid[u->i-1][u->j-1]);
  if(InBounds(u->i,u->j-1) && !IsOccupied(u->i,u->j-1)) s.push_back(grid[u->i][u->j-1]);
  if(InBounds(u->i+1,u->j-1) && !IsOccupied(u->i+1,u->j-1)) s.push_back(grid[u->i+1][u->j-1]);
};
bool Dstar::IsOccupied(int i, int j){
  //printf("grid.size() = %d\n",(int)grid.size());
  //printf(" check occupancy %d,%d\n",i,j);
  if(i >= (int) grid.size() || i < 0) return true;
  if(j >= (int) grid[0].size() || j < 0) return true;
  //if(grid[i][j].g == grid[i][j].rhs) return true;
  return (grid[i][j]->cost < 0);
};
void Dstar::MakePath(){

};
bool Dstar::InBounds(int i, int j){
    return ((i < (int) grid.size() && i >= 0) && (j < (int) grid[0].size()  && j >= 0));
};
double Dstar::GetCost(state *s1, state* s2){

};
