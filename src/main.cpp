#include "../include/dstar.h"
#include "../include/lpastar.h"

int main(){
    Dstar *dstar;
    LPAstar lpastar;
    size_t i,j,val;
    int avg;

    /*for(size_t i = 10; i < 500; i++){
        for(size_t j = 10; j < 300; j++){
            Dstar dstar;
            std::cout << i*j << " ";
            dstar.Main(i,j);
        }
    }*/
    val = 500*500;
    val /= 500;

    /*for(i = 10; i < 1500; i++){
        //dstar = new Dstar;
        std::cout << i << " ";
        avg = 0;
        for(j = 0; j < 5; j++){\
            dstar = new Dstar;
            avg += dstar->Main(i,i);
            free(dstar);
        }
        avg /= 5;
        std::cout << avg << std::endl;
        //dstar->Main(i,i);
        //free(dstar);
    }*/

    for(i = 10; i < 3000; i += 10){
        dstar = new Dstar;
        std::cout << i*i << " ";
        //avg = 0;
        //for(j = 0; j < 5; j++){
        //    dstar = new Dstar;
        //    avg += dstar->Main(i,i);
        //    free(dstar);
        //}
        //avg /= 5;
        std::cout << dstar->Main(i,i) << std::endl;
        free(dstar);
    }

    


    //dstar.Main(500,300);

    /*std::cout << "newgraph" << std::endl;
    std::cout << "xaxis min 0 max 1000000 log label: Number Nodes" << std::endl;
    std::cout << "yaxis min 0 max 10 linear label: Time (ms)" << std::endl;*/
    //dstar.JGRAPHPrintGrid();

    //lpastar.Main(5, 3);
    //lpastar.JGRAPHPrintGrid();
    
    return 0;
}