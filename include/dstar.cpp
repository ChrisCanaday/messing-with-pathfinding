#include "dstar.h"

// calculates h if needed then calculates k (priority)
priority Dstar::CalculateKey(state &s){
  priority tmp;
  s.h = CalculateHeuristic(*s_start,s);
  //std::cout << s.h << std::endl; 
  tmp.first = std::min(s.g, s.rhs) + s.h + k_m;
  tmp.second = std::min(s.g, s.rhs);
  return tmp;
}

// psuedo code rn (literally made the psuedocode real holy shit)
void Dstar::UpdateVertex(state &u){
  std::cout << U.GetSize() << std::endl;
  if(u.g != u.rhs && U.Present(u)){
    U.Update(u,CalculateKey(u));
    std:: cout << "ID = " << u.id << std::endl;
    grid[u.i][u.j] = u;
  }else if(u.g != u.rhs && !U.Present(u)){
    printf("add ");
    std::cout << CalculateKey(u).first << "|" << CalculateKey(u).second << std::endl;
    /*u.id = */U.Insert(u,CalculateKey(u));
    std:: cout << "ID = " << u.id << std::endl;
    grid[u.i][u.j] = u;
  }else if(u.g == u.rhs && U.Present(u)){
    printf("remove ");
    std::cout << u.g << " == " << u.rhs << std::endl;
    std:: cout << "ID = " << u.id << std::endl;
    grid[u.i][u.j] = u;
    U.Remove(u);
  }
}

void Dstar::Initialize(){
  while(!U.Empty()) U.Pop();                            // U = null
  k_m = 0;                                              // k_m = 0
  std::vector<state> tmp;
  changed = false;

  // set all states rhs and g to DBL_MAX
  for(int i = 0; i < (int) all_states.size(); i++){
    all_states[i].g = DBL_MAX;
    all_states[i].rhs = DBL_MAX;
    all_states[i].cost = 1;
  }


  for(int i = 0; i < 5; i++){
    tmp.clear();
    for(int j = 0; j < 3; j++){
      state s;
      if((i == 2 || i == 1/* || i == 3 || i == 4*/) && j == 1){
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
  original_start = s_start;
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
  //u.k.first = -1;
  //u.k.second = -1;

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

  if(InBounds(u.i+1,u.j) && !IsOccupied(u.i+1,u.j)) s.push_back(grid[u.i+1][u.j]);
  if(InBounds(u.i+1,u.j+1) && !IsOccupied(u.i+1,u.j+1)) s.push_back(grid[u.i+1][u.j+1]);
  if(InBounds(u.i,u.j+1) && !IsOccupied(u.i,u.j+1)) s.push_back(grid[u.i][u.j+1]);
  if(InBounds(u.i-1,u.j+1) && !IsOccupied(u.i-1,u.j+1)) s.push_back(grid[u.i-1][u.j+1]);
  if(InBounds(u.i-1,u.j) && !IsOccupied(u.i-1,u.j)) s.push_back(grid[u.i-1][u.j]);
  if(InBounds(u.i-1,u.j-1) && !IsOccupied(u.i-1,u.j-1)) s.push_back(grid[u.i-1][u.j-1]);
  if(InBounds(u.i,u.j-1) && !IsOccupied(u.i,u.j-1)) s.push_back(grid[u.i][u.j-1]);
  if(InBounds(u.i+1,u.j-1) && !IsOccupied(u.i+1,u.j-1)) s.push_back(grid[u.i+1][u.j-1]);
}

bool Dstar::InBounds(int i, int j){
  return ((i < (int) grid.size() && i >= 0) && (j < (int) grid[0].size()  && j >= 0));
}

bool Dstar::IsOccupied(int i, int j){
  //printf("grid.size() = %d\n",(int)grid.size());
  //printf(" check occupancy %d,%d\n",i,j);
  if(i >= (int) grid.size() || i < 0) return true;
  if(j >= (int) grid[0].size() || j < 0) return true;
  //if(grid[i][j].g == grid[i][j].rhs) return true;
  return (grid[i][j].cost < 0);
}

void Dstar::MakePath(){
  std::vector<state> s;
  state u, min2;
  priority min;
  int i;

  min.first = DBL_MAX;
  min.second = DBL_MAX;
  min2.k = min;


  path.clear();
  u = *s_start;
  path.push_back(u);
  while(u != *s_goal){
    GetPredecessors(u,s);
    min2.k = min;

    for(i = 0; i < (int) s.size(); i++){
      if(min2 > s[i]) min2 = s[i];
    }

    path.push_back(min2);
    u = min2;
  }
}

void Dstar::ComputeShortestPath(){
  state u, tmpnew;
  std::vector<state> s,s2;
  priority k_old, k_new;
  double g_old, mintmp;
  int i;

  //printf("before loop\n");
  std::cout << "SIZE: " << U.GetSize() << std::endl;
  u = U.Top();
  std::cout << "i: " << u.i << " j: " << u.j << std::endl;
  std::cout << u.k.first << "|" << u.k.second << std::endl;
  k_old = CalculateKey(*s_start);
  std::cout << k_old.first << "|" << k_old.second << std::endl;

  while(U.TopKey() < CalculateKey(*s_start) || s_start->rhs > s_start->g){
    u = U.Top();
    //printf("y.id %d\n",u.id);
    std::cout << "u.id " << u.id << std::endl;
    //printf("i:%d j:%d\n",u.i,u.j);
    std::cout << "i: " << u.i << " j: " << u.j << std::endl;
    k_old = U.TopKey();
    k_new = CalculateKey(u);
    //std::cout << u.g << " & " << u.rhs << std::endl;

    //printf("after init SIZE %d\n", U.GetSize());
    //std::cout << k_old.first << "|" << k_old.second << std::endl;
    //std::cout << k_new.first << "|" << k_new.second << std::endl;

    if(k_old < k_new){
      U.Update(u,k_new);
    }else if(u.g > u.rhs){
      //std::cout << u.g << " > " << u.rhs << std::endl;
      //printf("second if begon\n");
      u.g = u.rhs;
      //std::cout << u.g << " > " << u.rhs << std::endl;
      //u.cost = 0;
      grid[u.i][u.j] = u;
      //printf("uid %d\n",u.id);
      //printf("i:%d j:%d\n",u.i,u.j);
      U.Remove(u);
      all_states.push_back(u);
      //printf("2\n");

      // for all s predecessors s.rhs = min(s.rhs,c(s,u) + u.g)
      // then UpdateVertex(s)
      GetPredecessors(u,s);
      //printf(".SIZE() %d\n", (int)s.size());
      //std::cout << ".SIZE() " << s.size() << std::endl;

      for(i = 0; i < (int) s.size(); i++){
        if(s[i] != *s_goal) s[i].rhs = std::min(s[i].rhs, CalculateHeuristic(s[i],u) + u.g);
        UpdateVertex(s[i]);
      }
    }else{
      //printf("third if begon\n");
      g_old = u.g;
      u.g = DBL_MAX;
      
      GetPredecessors(u,s);

      for(i = 0; i < (int) s.size(); i++){
        if(s[i].rhs == CalculateHeuristic(s[i],u) + g_old){
          if(s[i] != *s_goal){
            GetSuccessors(s[i],s2);
            for(int j = 0; j < (int) s2.size(); j++){
              mintmp = std::min(mintmp, CalculateHeuristic(s[i],s2[j]) + s2[j].g);
            }
            //printf("mintmp\n");
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

  s_start->g = s_start->rhs;
  U.Remove(*s_start);
  //MakePath();
}

// main driver (react to changes)
void Dstar::Main(){
  double c_old;
  std::vector<state> tmp,tmp1;
  double min = DBL_MAX;
  priority big,neg;
  state s;
  int v = 0;
  neg.first = -1;
  neg.second = -1;

  Initialize();
  s_last = s_start;
  ComputeShortestPath();

  changed = true;
  GetSuccessors(grid[3][1],tmp);
  grid[3][1].cost = -1;
  for(size_t i = 0; i < tmp.size(); i++) changed_edges.push_back(tmp[i]);
  changed = true;
  GetSuccessors(grid[4][1],tmp);
  grid[4][1].cost = -1;
  for(size_t i = 0; i < tmp.size(); i++) changed_edges.push_back(tmp[i]);
  
  path.clear();
  path.push_back(*s_start);
  printf("\n\n");

  //for(int i = 0; i < (int) path.size(); i++){
        //printf("%d:%d ",path[i].i,path[i].j);
        //std::cout << path[i].k.first << "|" << path[i].k.second << " rhs: " << path[i].rhs << " g " << path[i].g << std::endl;
  //  }

  printf("%d:%d ",grid[1][0].i,grid[1][0].j);
  std::cout << grid[1][0].k.first << "|" << grid[1][0].k.second << " rhs: " << grid[1][0].rhs << " g " << grid[1][0].g << std::endl;
  printf("%d:%d ",grid[0][1].i,grid[0][1].j);
  std::cout << grid[0][1].k.first << "|" << grid[0][1].k.second << " rhs: " << grid[0][1].rhs << " g " << grid[0][1].g << std::endl;
  printf("%d:%d ",grid[1][2].i,grid[1][2].j);
  std::cout << grid[1][2].k.first << "|" << grid[1][2].k.second << " rhs: " << grid[1][2].rhs << " g " << grid[1][2].g << std::endl;
  printf("%d:%d ",grid[2][2].i,grid[2][2].j);
  std::cout << grid[2][2].k.first << "|" << grid[2][2].k.second << " rhs: " << grid[2][2].rhs << " g " << grid[2][2].g << std::endl;
  printf("%d:%d ",grid[3][2].i,grid[3][2].j);
  std::cout << grid[3][2].k.first << "|" << grid[3][2].k.second << " rhs: " << grid[3][2].rhs << " g " << grid[3][2].g << std::endl;
  printf("%d:%d ",grid[4][2].i,grid[4][2].j);
  std::cout << grid[4][2].k.first << "|" << grid[4][2].k.second << " rhs: " << grid[4][2].rhs << " g " << grid[4][2].g << std::endl;

  while(*s_start != *s_goal){
    printf("\n\n\n\n\n\n");
    if(s_start->rhs == DBL_MAX){
      std::cout << "NO PATH" << std::endl;
      return; // there is no path
    }

    GetSuccessors(*s_start, tmp1);
    std::cout << "TMP1.SIZE() " << tmp1.size() << std::endl;
    big.first = DBL_MAX;
    big.second = DBL_MAX;
    min = DBL_MAX;
    //s.k = big;
    /*if(tmp1.size() == 0){
      printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
      std::cout << path[0].i << "&" << path[0].j << std::endl;
      path.pop_back();
      s = path[path.size()-1];
      std::cout << "SSSSSSS: " << s.i << "&" << s.j << std::endl;
      //std::cout << s.i << " & " << s.j << std::endl;
      path.pop_back();
      std::cout <<" PATH SIZW :" << path.size() << std::endl;
      //if(path.size() == 0) ComputeShortestPath();
      //for(size_t i = 0; i < tmp1.size(); i++) if(s > tmp1[i]) s = tmp1[i];
    }*/
    for(size_t i = 0; i < tmp1.size(); i++){
      min = std::min(min,CalculateHeuristic(*s_start,tmp1[i]) + tmp1[i].g);
      if(min == CalculateHeuristic(*s_start,tmp1[i]) + tmp1[i].g) s = tmp1[i];
    }
    /*for(size_t i = 0; i < tmp1.size(); i++){
      if(s > tmp1[i]){
        s = tmp1[i];
      }
    }*/

    //*s_start = s;
    /*if(grid[s.i][s.j].k == neg){
      grid[s.i][s.j].k = CalculateKey(grid[s.i][s.j]);
    }*/
    /*if(s_start == &grid[s.i][s.j]){
      while(!U.Empty()) U.Pop();
      U.Insert(*s_goal,CalculateKey(*s_goal));
      s_start = original_start;
      s_last = s_start;
      k_m = 0;
      ComputeShortestPath();
    }*/
    std::cout << grid[0][1].k.first << "|" << grid[0][1].k.second << std::endl;
    s_start = &grid[s.i][s.j];
    if(tmp1.size() != 0)path.push_back(*s_start);

    std::cout << s_start->i << "&" << s_start->j << " | " << s_goal->i << "&" << s_goal->j << std::endl;
    std::cout << s_start->k.first << "|" << s_start->k.second << std::endl;
    std::cout << "g: " << s_start->g << " rhs: " << s_start->rhs << std::endl;
    std::cout << grid[0][0].k.first << "|" << grid[0][0].k.second << std::endl;

    //*s_start = path[1]; // set start to next thing in path
    //std::cout << s_start->rhs << std::endl;
    //printf("start not goal\n");
    std::cout << "START NOT GOAL" << std::endl;
    std::cout << U.GetSize() << std::endl;

    // move robot to s_start
    /*if(v == 1){
      //GetSuccessors(grid[4][1],tmp);
      GetPredecessors(grid[4][1],tmp1);
      grid[4][1].cost = -1;
      changed_edges.clear();
      //for(size_t i = 0; i < tmp.size(); i++) changed_edges.push_back(tmp[i]);
      for(size_t i = 0; i < tmp1.size(); i++) changed_edges.push_back(tmp1[i]);
      changed = true;
    }*/

    //std::cout << "CHANGE" << std::endl;
    // THIS PART IS THE NOT WORKING PART :D UNLESS THE NOT WORK IS CAUSED BY RUNNING ComputeShortestPath() To be determined but think it is here
    if(changed){
      min = DBL_MAX;
      v++;
      k_m = k_m + CalculateHeuristic(*s_last,*s_start);
      //std::cout << "HEURISTIC " << CalculateHeuristic(*s_last,*s_start) << std::endl;
      //std::cout << "K_M " << k_m << std::endl;
      s_last = s_start;

      for(size_t i = 0; i < changed_edges.size(); i++){
        c_old = changed_edges[i].h;
        changed_edges[i].h = CalculateHeuristic(changed_edges[i],*s_start);

        if(c_old > changed_edges[i].h){
          //printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
          if(changed_edges[i] != *s_goal){
            changed_edges[i].rhs = std::min(changed_edges[i].rhs, changed_edges[i].h + s_start->g);
            std::cout << changed_edges[i].rhs << "|" << changed_edges[i].h + s_start->g << std::endl;
          }
        }else if(changed_edges[i].rhs == c_old + s_start->g){
          if(changed_edges[i] != *s_goal){
            GetSuccessors(changed_edges[i],tmp1);
            for(size_t j = 0; j < tmp1.size(); j++){
              min = std::min(min,CalculateHeuristic(changed_edges[i],tmp1[j]) + tmp1[j].g);
              //tmp1[i].k = CalculateKey(tmp1[i]);
            }
            changed_edges[i].rhs = min;
          }
        }
        std::cout << "UPDATE VERTEX" << std::endl;
        std::cout << changed_edges[i].i << " & " << changed_edges[i].j << std::endl;
        std::cout << changed_edges[i].k.first << "|" << changed_edges[i].k.second << std::endl;
        std::cout << "k_m: " << k_m << std::endl;
        UpdateVertex(changed_edges[i]);
      }
      changed_edges.clear();
      changed = false;
      std::cout << "ComputeShortestPath()" << std::endl;
      ComputeShortestPath();
    }
    //ComputeShortestPath();
  }
  
}