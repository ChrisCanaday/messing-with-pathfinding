#include "state.h"

state::state(){
    g = DBL_MAX/2;
    rhs = DBL_MAX/2;
    h = 0.0;
    i = -1;
    j = -1;
    id = -1;
    k.first = DBL_MAX/2;
    k.second = DBL_MAX/2;
}