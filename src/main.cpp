#include "../include/dstar.h"
#include "../include/lpastar.h"

int main(){
    Dstar dstar;
    LPAstar lpastar;
    //int i,j;
    state min2;
    std::vector<state> s;
    std::vector<state> path;
    priority min;
    min.first = DBL_MAX;
    min.second = DBL_MAX;
    min2.k = min;

    //dstar.Main(5,3);
    //dstar.JGRAPHPrintGrid();

    lpastar.Main(5, 3);
    //lpastar.JGRAPHPrintGrid();
    

    /*for(i = 0; i < (int) dstar.grid.size(); i++){
        for(j = 0; j < (int) dstar.grid[0].size(); j++){
            printf("%d:%d ",i,j);
            std::cout << dstar.grid[i][j]->k.first << "|" << dstar.grid[i][j]->k.second << std::endl;
        }
    }
    printf("\nALLSTATES\n");
    printf("\nPATH\n");
    printf("path.size() %ld\n",dstar.path.size());
    //std::cout << "path.size() " << dstar.path.size()
    for(i = 0; i < (int) dstar.path.size(); i++){
        printf("%d:%d ",dstar.path[i]->i,dstar.path[i]->j);
        std::cout << dstar.path[i]->k.first << "|" << dstar.path[i]->k.second << " rhs: " << dstar.path[i]->rhs << " g " << dstar.path[i]->g << std::endl;
    }
    
    printf("\nHEAP\n");
    dstar.U.Print();*/

    //dstar.JGRAPHPrintGrid();
    
    return 0;
}