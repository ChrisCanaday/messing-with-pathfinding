#include "priorityq.h"

PQ::PQ(){
    inf.first = DBL_MAX;
    inf.second = DBL_MAX;
    size = 0;
    // setup and add all nodes to the PQ
}

// insert state s with priority k
// set k in the s then insert most likely
void PQ::Insert(state s, priority k){
    int i;

    // get index
    i = size;

    // set priority and the id
    s.k = k;
    s.id = i;

    heap.push_back(s);
    size++;

    // percolate up and swap if necessary
    PercolateUp(s);
}

void PQ::PercolateUp(state s){
    int i = s.id, p;

    printf("i: %d\n",i);
    while(i > 0){
        p = (i-1)/2;

        if(heap[p] > s){
            heap[i] = heap[p];
            heap[p] = s;
            heap[i].id = i;
            i = p;
            s.id = p;
        }else{
            return;
        }
    }
}

// update s's k and make sure its position updates
void PQ::Update(state s, priority k){
    int p, ileft, iright;

    if(s.k.first == k.first && s.k.second == k.second) return;

    // update s's values
    s.k = k;
    heap[s.id] = s;

    // get parent and children
    p = (s.id-1)/2;
    ileft = s.id*2+1;
    iright = s.id*2+2;

    // if smaller then parent then percolate up
    // if bigger than children then percolate down
    if(heap[p] > s){
        PercolateUp(s);
    }else if((ileft < size-1 && iright < size-1) && (s > heap[ileft] || s > heap[iright])){
        PercolateDown(ileft,iright);
    }
}

// return the smallest state (aka the top)
state PQ::Top(){
    return heap[0];
}

// return the k of the Top state (call top then return k)
// returns [DBL_MAX,DBL_MAX] if PQ is empty
priority PQ::TopKey(){
    if(size == 0) return inf;
    return Top().k;
}

// remove the state from the PQ
void PQ::Remove(state s){
    state tmp;
    int index = s.id;

    if(size == 0) return;
    if(s.id == -1) return;

    // move the last item in the list to the root
    heap[index] = heap[size-1];
    heap[index].id = index;
    s.id = -1;
    heap.pop_back();
    size--;

    // percolate down to move things into correct place
    PercolateDown(2*heap[index].id+1, 2*heap[index].id+2);
}

// percolates down
void PQ::PercolateDown(int left, int right){
    int p, lesser;
    state tmp;

    // go through all children
    while(left < size && right < size){

        // the children's parent index
        p = (left-1)/2;

        // choose the lesser one
        lesser = (heap[left] > heap[right]) ? right : left;

        // swap the lesser one with the parent
        tmp = heap[p];
        heap[p] = heap[lesser];
        heap[lesser] = tmp;

        // update id's
        heap[lesser].id = right;
        heap[p].id = p;

        // calculate the next children
        left = 2*lesser+1;
        right = 2*lesser+2;
    }
}

// obvious
bool PQ::Empty(){
    return (size == 0);
}

// remove the first item in the PQ
void PQ::Pop(){
    Remove(Top());
}

bool PQ::Present(state s){
    return (s.id != -1 && s.id < size);
}

// clears list and prints at same time (prints in order)
void PQ::Print(){
    int i, num = size;
    state tmp;

    for(i = 0; i < num; i++){
        tmp = Top();

        std::cout << tmp.k.first << "|" << tmp.k.second << std::endl;
        Remove(tmp);
    }
}