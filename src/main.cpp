#include "../include/dstar.h"

int main(){
    Dstar dstar;
    int i,j;
    state u, min2;
    std::vector<state> s;
    std::vector<state> path;
    priority min;
    min.first = DBL_MAX;
    min.second = DBL_MAX;
    min2.k = min;

    //dstar.Initialize();
    dstar.Main();

    for(i = 0; i < (int) dstar.grid.size(); i++){
        for(j = 0; j < (int) dstar.grid[0].size(); j++){
            printf("%d:%d ",i,j);
            std::cout << dstar.grid[i][j].k.first << "|" << dstar.grid[i][j].k.second << std::endl;
        }
    }
    printf("\n\n");

    for(i = 0; i < (int) dstar.all_states.size(); i++){
        printf("%d:%d ",dstar.all_states[i].i,dstar.all_states[i].j);
        std::cout << dstar.all_states[i].k.first << "|" << dstar.all_states[i].k.second << std::endl;
    }

    u = *dstar.s_start;
    path.push_back(u);
    while(u != *dstar.s_goal){
        dstar.GetPredecessors(u,s);
        min2.k = min;

        for(i = 0; i < (int) s.size(); i++){
            if(min2 > s[i]) min2 = s[i];
        }

        path.push_back(min2);
        u = min2;
    }
    printf("\n\n");
    for(i = 0; i < (int) path.size(); i++){
        printf("%d:%d ",path[i].i,path[i].j);
        std::cout << path[i].k.first << "|" << path[i].k.second << " rhs: " << path[i].rhs << " g " << path[i].g << std::endl;
    }
    
    
    return 0;
}