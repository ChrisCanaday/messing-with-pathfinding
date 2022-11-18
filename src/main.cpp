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
    printf("\nALLSTATES\n");

    for(i = 0; i < (int) dstar.all_states.size(); i++){
        printf("%d:%d ",dstar.all_states[i].i,dstar.all_states[i].j);
        std::cout << dstar.all_states[i].k.first << "|" << dstar.all_states[i].k.second << std::endl;
    }

    u = *dstar.s_start;
    /*path.push_back(u);
    while(u != *dstar.s_goal){
        dstar.GetPredecessors(u,s);
        min2.k = min;

        for(i = 0; i < (int) s.size(); i++){
            if(min2 > s[i]) min2 = s[i];
        }

        path.push_back(min2);
        u = min2;
    }*/
    printf("\nPATH\n");
    printf("path.size() %ld\n",dstar.path.size());
    //std::cout << "path.size() " << dstar.path.size()
    for(i = 0; i < (int) dstar.path.size(); i++){
        printf("%d:%d ",dstar.path[i].i,dstar.path[i].j);
        std::cout << dstar.path[i].k.first << "|" << dstar.path[i].k.second << " rhs: " << dstar.path[i].rhs << " g " << dstar.path[i].g << std::endl;
    }
    
    printf("\nHEAP\n");
    for(i = 0; i < dstar.U.heap.size(); i++){
        printf("%d:%d ",dstar.U.heap[i].i,dstar.U.heap[i].j);
        std::cout << dstar.U.heap[i].k.first << "|" << dstar.U.heap[i].k.second << " rhs: " << dstar.U.heap[i].rhs << " g " << dstar.U.heap[i].g << std::endl;
    }

    /*PQ U;
    //state s;

    for(int i = 0; i < 10; i++){
        state s;

        s.k.first = i%2;
        s.k.second = i;
        s.i = i*2;
        s.j = i;
        U.Insert(s,s.k);
        printf("s.id: %d\n",s.id);
    }

    state u;
    u.k.first = 100;
    u.k.second = 100;
    u.id = 5;
    u.i = 98;
    u.j = 5;
    U.GetSize();
    U.Remove(u);
    U.GetSize();*/
    
    return 0;
}