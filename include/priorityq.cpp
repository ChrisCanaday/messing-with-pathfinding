#include "priorityq.h"

PQ::PQ(){
    // init
}

void PQ::Insert(state s, std::pair<double,double> k){
    // insert state s with priority k

    // set k in the s then insert most likely
}

void PQ::Update(state s, std::pair<double,double> k){
    // update s's k and make sure its position updates
}

state PQ::Top(){
    // return the smallest state (aka the top)
}

std::pair<double,double> PQ::TopKey(){
    // return the k of the Top state (call top then return k)
}

void PQ::Remove(state s){
    // remove the state from the PQ
}

// obvious
bool PQ::Empty(){
    return (size == 0);
}