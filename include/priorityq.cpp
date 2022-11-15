#include "priorityq.h"

template <class T, class U>
PQ<T,U>::PQ(){
    // init
}

template <class T, class U>
void PQ<T,U>::Insert(T s, U k){
    // insert state s with priority k

    // set k in the s then insert most likely
}

template <class T, class U>
void PQ<T,U>::Update(T s, U k){
    // update s's k and make sure its position updates
}

template <class T, class U>
state PQ<T,U>::Top(){
    // return the smallest state (aka the top)
}

template <class T, class U>
U PQ<T,U>::TopKey(){
    // return the k of the Top state (call top then return k)
}

template <class T, class U>
void PQ<T,U>::Remove(T s){
    // remove the state from the PQ
}

// obvious
template <class T, class U>
bool PQ<T,U>::Empty(){
    return (size == 0);
}