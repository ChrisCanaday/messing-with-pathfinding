#include "state.h"

state::state(){
    g = DBL_MAX;
    rhs = DBL_MAX;
    h = 0.0;
    i = -1;
    j = -1;
    id = -1;
    k.first = DBL_MAX;
    k.second = DBL_MAX;
}