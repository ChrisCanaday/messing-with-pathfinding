#include "../include/dstar.h"
#include <iostream>

int main(){
    Dstar dstar;
    state *tmp;
    state tmp1;

    for(int i = 0; i < 10; i++){
        tmp = new state;
        //tmp->g = .5*i;
        tmp->k.first = 1;
        tmp->k.second = i+1;
        dstar.U.push(*tmp);
    }

    while(!dstar.U.empty()){
        tmp1 = dstar.U.top();
        dstar.U.pop();
        std::cout << tmp1.k.first << "|" << tmp1.k.second << std::endl;
    }
    
    return 0;
}