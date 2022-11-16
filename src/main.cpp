#include "../include/dstar.h"

int main(){
    Dstar dstar;
    int i,j;

    //dstar.Initialize();
    dstar.Main();

    for(i = 0; i < (int) dstar.grid.size(); i++){
        for(j = 0; j < (int) dstar.grid[0].size(); j++){
            printf("%d:%d ",i,j);
            std::cout << dstar.grid[i][j].k.first << "|" << dstar.grid[i][j].k.second << std::endl;
        }
    }
    
    return 0;
}