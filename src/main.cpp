#include "../include/dstar.h"

int main(){
    //Dstar dstar;
    state *tmp;
    std::pair<double,double> k;
    state tmp1;
    PQ priority_queue;

    for(int i = 0; i < 10; i++){
        tmp = new state;
        k.first = i%2;
        k.second = i;
        priority_queue.Insert(*tmp,k);
    }

    priority_queue.Print();

    for(int i = 0; i < 10; i++){
        tmp = new state;
        k.first = i%2;
        k.second = i;
        priority_queue.Insert(*tmp,k);
    }

    k.first = 100;
    k.second = 2.3;
    priority_queue.Update(*tmp,k);
    priority_queue.Print();

    /*for(int i = 0; i < 10; i++){
        tmp1 = priority_queue.Top();
        
    }*/
    //printf("afterprint\n");
    
    return 0;
}