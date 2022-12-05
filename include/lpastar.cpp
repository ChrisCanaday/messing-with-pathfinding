#include "lpastar.h"

/* Calculates the key (priority) of the state s */
priority LPAstar::CalculateKey(state *s)
{
  priority ans;

  ans.first = std::min(s->g, s->rhs) + CalculateHeuristic(s_goal, s);
  ans.second = std::min(s->g, s->rhs);

  return ans; // [min(s->g,s->rhs) + s->h; min(s->g,s->rhs)]
};

/* Initializes the Dstar class*/
void LPAstar::Initialize(int height, int width)
{
  std::chrono::steady_clock::time_point begin, end;
  std::vector<state *> tmp;
  state *s;

  U.Clear(); // U = NULL
  
  begin = std::chrono::steady_clock::now();


  // init grid
  for (int i = 0; i < height; i++){
    tmp.clear();
    for (int j = 0; j < width; j++){
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
  int k,l;

  /*for(int i = 0; i < (height)*(width)/2; i++){
    //srand(time(0));
    k = rand();
    k = k % height;
    l = rand();
    l = l % width;
    if((k != 0 && l != 0) && (k != height-1 && l != width-1)){
      grid[k][l]->cost = -1;
    }
  }*/




  //std::cout << "after" << std::endl;

  // set start and goal
  s_start = grid[1][0];
  s_goal = grid[height-1][width-1];
  changed = false;

  // setup PQ
  s_start->rhs = 0;
  U.Insert(s_start, CalculateKey(s_start));
  end = std::chrono::steady_clock::now();

  //std::cout << "Initialization Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " [ms]" << std::endl;
};

/* Updates state u in the PQ */
void LPAstar::UpdateVertex(state *u)
{
  std::vector<state *> tmp;
  double tmprhs = inf;

  // if not goal set rhs
  if (*u != *s_start){
    GetPredecessors(u, tmp);

    for (size_t i = 0; i < tmp.size(); i++){
      tmprhs = std::min(tmprhs, CalculateHeuristic(tmp[i], u) + tmp[i]->g);
    }
    u->rhs = tmprhs;

    //JGRAPHPrintGrid();
  }

  // if in the PQ remove it
  if (U.Present(u)) U.Remove(u);

  // if locally inconsistent then add to the PQ
  if (u->rhs != u->g) U.Insert(u, CalculateKey(u));
};

/* LPA* */
void LPAstar::ComputeShortestPath()
{
  state *u;
  std::vector<state *> tmp;
  size_t i;

  while (U.TopKey() < CalculateKey(s_goal) || s_goal->rhs != s_goal->g){
    u = U.Pop();
    s_last = u;
    //std::cerr << "I: " << u->i << " J: " << u->j << std::endl;

    // if overly consistent make it locally consistent
    // then update all predecessors
    if (u->g > u->rhs){
      u->g = u->rhs;
      GetSuccessors(u, tmp);
      for (i = 0; i < tmp.size(); i++){
        UpdateVertex(tmp[i]);
      }
    }else{

      // set estimated distance from start to infinity
      // them update all predecessors and self
      u->g = inf;
      GetSuccessors(u, tmp);
      tmp.push_back(u);
      for (i = 0; i < tmp.size(); i++){
        UpdateVertex(tmp[i]);
      }
    }
    JGRAPHPrintGrid();
  }
  s_last = NULL;
};

/* Main D* Lite Driver */
void LPAstar::Main(int height, int width)
{
  std::vector<state *> tmp;
  state *tmpstate;
  double min, oldmin;
  size_t i, it = 0;

  // init, make initial run, start path
  Initialize(height, width);

  std::chrono::steady_clock::time_point begin, end;
  JGRAPHPrintGrid();

  begin = std::chrono::steady_clock::now();
  //std::cout << "A" << std::endl;
  //ComputeShortestPath();

  end = std::chrono::steady_clock::now();
  //path.push_back(s_start);

  //std::cout << "ComputeShortestPath() Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " [ms]" << std::endl;
  //JGRAPHPrintGrid();

  //JGRAPHPrintGrid();
  //std::cout << "B" << std::endl;

  // test change
  //changed = true;
  //GetSuccessors(grid[4][1], tmp);
  //grid[4][1]->cost = -1;
  //for (size_t i = 0; i < tmp.size(); i++) changed_edges.push_back(tmp[i]);
  s_last = NULL;
  //JGRAPHPrintGrid();
  for( ; ; ){
    ComputeShortestPath();

    //while(!changed){};
    if(!changed){
        //std::cerr << "before" << std::endl;
        path.clear();
        path.push_back(s_goal);
        while(*s_start != *s_goal){
            //std::cerr << "before2" << std::endl;
            GetPredecessors(s_goal, tmp);

            min = inf;
            oldmin = min;
            for (i = 0; i < tmp.size(); i++){
                min = std::min(min, CalculateHeuristic(s_goal, tmp[i]) + tmp[i]->g);
                if (min != oldmin){
                    tmpstate = tmp[i];
                    oldmin = min;
                }
            }

            // set start to the next step and add it to the path
            s_goal = tmpstate;
            //std::cerr << s_goal->i << ":" << s_goal->j << std::endl;
            path.push_back(s_goal);
        }
        //std::cerr << "after" << std::endl;

        /*for(i = 0; i < path.size(); i++){
            std::cerr << path[i]->i << ":" << path[i]->j << std::endl;
        }*/
        s_goal = grid[grid.size()-1][grid[0].size()-1];
        JGRAPHPrintGrid();
        //path.clear();

        changed = true;
        GetSuccessors(grid[4][1], tmp);
        grid[4][1]->cost = -1;
        for (size_t i = 0; i < tmp.size(); i++) changed_edges.push_back(tmp[i]);
        
        if(it == 1) break;
        it++;
        //break;
    }

    if (changed){

      //std::cerr << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;

      // update all of the changed nodes
      for (i = 0; i < changed_edges.size(); i++){
        UpdateVertex(changed_edges[i]);
      }

      // update every node in the PQ
      //U.GetAllNodes(tmp);

      /*for (i = 0; i < tmp.size(); i++){
        U.Update(tmp[i], CalculateKey(tmp[i]));
      }*/

      // recompute the path
      //ComputeShortestPath();
      changed = false;
    }

  }
};

/* Calculates the cost from one node to another. Uses Euclidean Distance */
double LPAstar::CalculateHeuristic(const state *to, const state *from) const
{
  double di = abs(to->i - from->i);
  double dj = abs(to->j - from->j);

  return sqrt(di * di + dj * dj);
};

/* Returns all adjacent nodes that are legal */
void LPAstar::GetPredecessors(const state *u, std::vector<state *> &s)
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
void LPAstar::GetSuccessors(const state *u, std::vector<state *> &s)
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
bool LPAstar::IsOccupied(const int i, const int j) const
{
  // check to see if you are outside of the grid
  if (i >= (int)grid.size() || i < 0) return true;
  if (j >= (int)grid[0].size() || j < 0) return true;
  
  // return if the node is a wall
  return (grid[i][j]->cost < 0);
};

void LPAstar::PrintBox(int i, int j){
  //std::cout << "newline poly pfill 0 pts" << std::endl;
  if(grid[i][j]->cost == -1){
    if(!(grid.size() > 8 || grid[0].size() > 4)){
      std::cout << "newline poly pfill 0 pts" << std::endl;
    }else{
      std::cout << "newline poly pfill 0 color 0 0 0 pts" << std::endl;
    }
  }else{
    if(*grid[i][j] == *s_start){
      if(*s_start == *s_goal){
        if(!(grid.size() > 8 || grid[0].size() > 4)){
          std::cout << "newline poly pcfill 1 0 1 pts" << std::endl;
        }else{
          std::cout << "newline poly pcfill 1 0 1 color 1 0 1 pts" << std::endl;
        }
      }else{
        if(!(grid.size() > 8 || grid[0].size() > 4)){
          if(s_last != NULL && *s_last == *grid[i][j]){
            std::cout << "newline poly pcfill 1 0 1 pts" << std::endl;
          }else{
            std::cout << "newline poly pcfill 1 128 0 pts" << std::endl;
          }
        }else{
          if(s_last != NULL && *s_last == *grid[i][j]){
            std::cout << "newline poly pcfill 1 0 1 pts" << std::endl;
          }else{
            std::cout << "newline poly pcfill 1 128 0 color 1 128 0 pts" << std::endl;
          }
        }
      }
      //std::cout << "newline poly pcfill 1 128 0 pts" << std::endl;
    }else{
      if(*grid[i][j] == *s_goal){
        if(!(grid.size() > 8 || grid[0].size() > 4)){
          if(s_last != NULL && *s_last == *grid[i][j]){
            std::cout << "newline poly pcfill 1 0 1 pts" << std::endl;
          }else{
            std::cout << "newline poly pcfill 0 128 0 pts" << std::endl;
          }
        }else{
          if(s_last != NULL && *s_last == *grid[i][j]){
            std::cout << "newline poly pcfill 1 0 1 color 1 0 1 pts" << std::endl;
          }else{
            std::cout << "newline poly pcfill 0 128 0 color 0 128 0 pts" << std::endl;
          }
        }
      }else{
        //std::cerr << "BEFOREPATH" << std::endl;
        if(OnPath(i,j)){
            //std::cerr << "ONPATH" << std::endl;
            if(!(grid.size() > 8 || grid[0].size() > 4)){
              if(s_last != NULL && *s_last == *grid[i][j]){
                std::cout << "newline poly pcfill 1 0 1 pts" << std::endl;
              }else{
                std::cout << "newline poly pcfill 0 1 2 pts" << std::endl;
              }
            }else{
              if(s_last != NULL && *s_last == *grid[i][j]){
                std::cout << "newline poly pcfill 1 0 1 color 1 0 1 pts" << std::endl;
              }else{
                std::cout << "newline poly pcfill 0 1 2 color 0 1 2 pts" << std::endl;
              }
            }
        }else{
          if(!(grid.size() > 8 || grid[0].size() > 4)){
            if(s_last != NULL && *s_last == *grid[i][j]){
              std::cout << "newline poly pcfill 1 0 1 pts" << std::endl;
            }else{
              std::cout << "newline poly pfill 1 pts" << std::endl;
            }
          }else{
            if(s_last != NULL && *s_last == *grid[i][j]){
              std::cout << "newline poly pcfill 1 0 1 color 1 0 1 pts" << std::endl;
            }else{
              std::cout << "newline poly pfill 1 color 1 1 1 pts" << std::endl;
            }
          }
        }
      }
    }
  }

  /*std::cout << i << " " << -1*j << std::endl;
  std::cout << (i+1) << " " << -1*j << std::endl;
  std::cout << (i+1) << " " << -1*(j+1) << std::endl;
  std::cout << i << " " << -1*(j+1) << std::endl;
  std::cout << i << " " << -1*j << std::endl;*/
  //if(!(grid.size() > 8 || grid[0].size() > 4)){
    std::cout << j << " " << -1*i << std::endl;
    std::cout << (j+1) << " " << -1*i << std::endl;
    std::cout << (j+1) << " " << -1*(i+1) << std::endl;
    std::cout << j << " " << -1*(i+1) << std::endl;
    std::cout << j << " " << -1*i << std::endl;
  //}
  /*std::cout << j << " " << -1*i << std::endl;
  std::cout << (j+1) << " " << -1*i << std::endl;
  std::cout << (j+1) << " " << -1*(i+1) << std::endl;
  std::cout << j << " " << -1*(i+1) << std::endl;
  std::cout << j << " " << -1*i << std::endl;*/

  double a,b, c;
  a = j+.05;
  b = -1*i-.2;
  c = inf;
  std::cout << std::setprecision(3);

  if(grid.size() > 8 || grid[0].size() > 4 || grid[i][j]->cost == -1) return;
  if(grid[i][j]->g == c){
    std::cout << "newstring hjl vjc fontsize 8 x " << a << " y " << b  << " : g: " << "INF" << std::endl;
    //printf("%2.2f\n",);
  }else{
    std::cout << "newstring hjl vjc fontsize 8 x " << a << " y " << b  << " : g: ";
    printf("%2.2f\n",grid[i][j]->g);
  }

  //a += .1;
  b -= .3;
  if(grid[i][j]->rhs == c){
    std::cout << "newstring hjl vjc fontsize 8 x " << a << " y " << b  << " : rhs: " << "INF" << std::endl;
    //printf("%2.2f\n",);
  }else{
    std::cout << "newstring hjl vjc fontsize 8 x " << a << " y " << b  << " : rhs: ";
    printf("%2.2f\n",grid[i][j]->rhs);
  }
  b -= .3;
  if(grid[i][j]->k.first == c && grid[i][j]->k.second != c){
    std::cout << "newstring hjl vjc fontsize 8 x " << a << " y " << b  << " : [INF,";
    printf("%2.2f]\n",grid[i][j]->k.second);
  }else if(grid[i][j]->k.first != c && grid[i][j]->k.second == c){
    std::cout << "newstring hjl vjc fontsize 8 x " << a << " y " << b  << " : [";
    printf("%2.2f,INF]\n",grid[i][j]->k.first);
  }else if(grid[i][j]->k.first == c && grid[i][j]->k.second == c){
    std::cout << "newstring hjl vjc fontsize 8 x " << a << " y " << b  << " : [" << "INF,INF]" << std::endl;
  }else if(grid[i][j]->k.first != c && grid[i][j]->k.second != c){
    std::cout << "newstring hjl vjc fontsize 8 x " << a << " y " << b  << " : [";
    printf("%2.2f,",grid[i][j]->k.first);
    printf("%2.2f]\n",grid[i][j]->k.second);
  }
}

void LPAstar::JGRAPHPrintGrid(){
  std::cout << "newgraph" << std::endl;
  //std::cout << "xaxis nodraw" << std::endl;
  //int s = (int) (grid[0].size()-1);
  std::cout << "xaxis min -1 max " << grid[0].size()+1 << " nodraw" << std::endl;
  //std::cout << "yaxis nodraw" << std::endl;
  int s = (int) (grid.size()+1);
  std::cout << "yaxis min " << -1*s << " max 1 nodraw" << std::endl;

  //PrintBox(0,0);
  //PrintBox(0,1);

  for(size_t i = 0; i < grid.size(); i++){
    for(size_t j = 0; j < grid[0].size(); j++){
      PrintBox(i,j);
    }
  }
}

bool LPAstar::OnPath(int i, int j){
    //std::cerr << "NEW I: " << i << ":NEW J: " << j << std::endl; 
    for(size_t k= 0; k < path.size(); k++){
        if(path[k]->i == i && path[k]->j == j) return true;
    }
    return false;
}