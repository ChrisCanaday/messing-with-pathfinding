#include "dstar.h"

// calculates h if needed then calculates k (priority)
priority Dstar::CalculateKey(state &s){
  priority tmp;
  if(s.h == 0.0) s.h = CalculateHeuristic(*s_start,s);
  tmp.first = std::min(s.g, s.rhs) + s.h + k_m;
  tmp.second = std::min(s.g, s.rhs);
  return tmp;
}

// psuedo code rn (literally made the psuedocode real holy shit)
void Dstar::UpdateVertex(state &u){
  if(u.g != u.rhs && U.Present(u)){
    U.Update(u,CalculateKey(u));
    //grid[u.i][u.j] = u;
  }else if(u.g != u.rhs && !U.Present(u)){
    printf("add\n");
    /*u.id = */U.Insert(u,CalculateKey(u));
   // grid[u.i][u.j] = u;
  }else if(u.g == u.rhs && U.Present(u)){
    printf("remove\n");
    U.Remove(u);
  }
}

void Dstar::Initialize(){
  while(!U.Empty()) U.Pop();                            // U = null
  k_m = 0;                                              // k_m = 0
  std::vector<state> tmp;

  // set all states rhs and g to DBL_MAX
  for(int i = 0; i < (int) all_states.size(); i++){
    all_states[i].g = DBL_MAX/2;
    all_states[i].rhs = DBL_MAX/2;
    all_states[i].cost = 1;
  }


  for(int i = 0; i < 5; i++){
    tmp.clear();
    for(int j = 0; j < 3; j++){
      state s;
      if((i == 2 || i == 1) && j == 1){
        s.cost = -1;
      }else{
        s.cost = 1;
      }

      s.i = i;
      s.j = j;
      tmp.push_back(s);
    }
    grid.push_back(tmp);
  }


  s_goal = &grid[4][2];
  s_start = &grid[1][0];
  s_goal->rhs = 0;                                       // rhs(s_goal) = 0
  //CalculateKey(s_goal);                               // [h(s_start, s_goal); 0]
  U.Insert(*s_goal,CalculateKey(*s_goal));                // U.Insert(s_goal,[h(s_start, s_goal); 0])
}

// returns euclidean distance between node from and to
double Dstar::CalculateHeuristic(const state &to, const state &from) const{
  int di = abs(from.i - to.i);
  int dj = abs(from.j - to.j);

  return sqrt(di*di + dj*dj);
}

void Dstar::GetPredecessors(state &u, std::vector<state> &s){
  s.clear();
  u.k.first = -1;
  u.k.second = -1;

  // check every block around us
  //printf("before block\n");
  if(!IsOccupied(u.i+1,u.j)) s.push_back(grid[u.i+1][u.j]);
  if(!IsOccupied(u.i+1,u.j+1)) s.push_back(grid[u.i+1][u.j+1]);
  if(!IsOccupied(u.i,u.j+1)) s.push_back(grid[u.i][u.j+1]);
  if(!IsOccupied(u.i-1,u.j+1)) s.push_back(grid[u.i-1][u.j+1]);
  if(!IsOccupied(u.i-1,u.j)) s.push_back(grid[u.i-1][u.j]);
  if(!IsOccupied(u.i-1,u.j-1)) s.push_back(grid[u.i-1][u.j-1]);
  if(!IsOccupied(u.i,u.j-1)) s.push_back(grid[u.i][u.j-1]);
  if(!IsOccupied(u.i+1,u.j-1)) s.push_back(grid[u.i+1][u.j-1]);
}

void Dstar::GetSuccessors(state &u, std::vector<state> &s){
  s.clear();
  if(IsOccupied(u.i,u.j)) return;

  s.push_back(grid[u.i+1][u.j]);
  s.push_back(grid[u.i+1][u.j+1]);
  s.push_back(grid[u.i][u.j+1]);
  s.push_back(grid[u.i-1][u.j+1]);
  s.push_back(grid[u.i-1][u.j]);
  s.push_back(grid[u.i-1][u.j-1]);
  s.push_back(grid[u.i][u.j-1]);
  s.push_back(grid[u.i+1][u.j-1]);
}

bool Dstar::IsOccupied(int i, int j){
  //printf("grid.size() = %d\n",(int)grid.size());
  //printf(" check occupancy %d,%d\n",i,j);
  if(i >= grid.size() || i < 0) return true;
  if(j >= grid[0].size() || j < 0) return true;
  return (grid[i][j].cost < 0);
}

void Dstar::ComputeShortestPath(){
  state u, tmpnew;
  std::vector<state> s,s2;
  priority k_old, k_new;
  double g_old, mintmp;
  int i;

  //printf("before loop\n");
  while(U.TopKey() < CalculateKey(*s_start) || s_start->rhs > s_start->g){
    u = U.Top();
    printf("y.id %d\n",u.id);
    k_old = U.TopKey();
    k_new = CalculateKey(u);

    printf("after init SIZE %d\n", U.GetSize());
    std::cout << k_old.first << "|" << k_old.second << std::endl;
    std::cout << k_new.first << "|" << k_new.second << std::endl;

    //tmpnew.k = k_new;
    if(k_old < k_new){
      //printf("first if begon\n");
      U.Update(u,k_new);
      //printf("first if end\n");
    }else if(u.g > u.rhs){
      std::cout << u.g << " > " << u.rhs << std::endl;
      printf("second if begon\n");
      u.g = u.rhs;
      std::cout << u.g << " > " << u.rhs << std::endl;
      u.cost = 0;
      grid[u.i][u.j] = u;
      printf("uid %d\n",u.id);
      printf("i:%d j:%d\n",u.i,u.j);
      //printf("1\n");
      U.Remove(u);
      all_states.push_back(u);
      //printf("2\n");

      // for all s predecessors s.rhs = min(s.rhs,c(s,u) + u.g)
      // then UpdateVertex(s)
      GetPredecessors(u,s);
      printf(".SIZE() %d\n", (int)s.size());
      //printf("3\n");
      for(i = 0; i < (int) s.size(); i++){
        //printf("4 %d\n",i);
        //printf("s[%d].i = %d: s[%d].j = %d\n",i,s[i].i,i,s[i].j);
        if(s[i] != *s_goal && s[i].cost > 0) s[i].rhs = std::min(s[i].rhs, CalculateHeuristic(s[i],u) + u.g);
        //printf("4:2\n");
        UpdateVertex(s[i]);
        //printf("update\n");
      }
      //printf("second if en\n");
    }else{
      printf("third if begon\n");
      g_old = u.g;
      u.g = DBL_MAX/2;
      
      GetPredecessors(u,s);

      for(i = 0; i < (int) s.size(); i++){
        if(s[i].rhs == CalculateHeuristic(s[i],u) + g_old){
          if(s[i] != *s_goal){
            GetSuccessors(s[i],s2);
            for(int j = 0; j < (int) s2.size(); j++){
              mintmp = std::min(mintmp, CalculateHeuristic(s[i],s2[j]) + s2[j].g);
            }
            printf("mintmp\n");
            s[i].rhs = mintmp;
          }
          UpdateVertex(s[i]);
        }
      }
      //printf("third if end\n");
      // for all s pred of u
      // do shit (look at doc)
      // UpdateVertex s at end
    }
  }
}

// main driver (react to changes)
void Dstar::Main(){
  s_last = s_start;
  Initialize();
  printf("compute\n");
  ComputeShortestPath();

  /*while(s_start != s_goal){
    
  }*/
}