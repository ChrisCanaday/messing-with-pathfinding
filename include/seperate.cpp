#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

// seperates jgraphs into different files
int main(int argc, char **argv){
    string input, name = "t", end = ".txt", filename, filename2, s, commandname, end2 = ".jpg";
    int i = 0, j;
    FILE *fout = NULL;
    
    while(getline(cin,input)){
        if(input == "newgraph"){
            if(fout != NULL) fclose(fout);
            s = to_string(i);
            filename = name + s + end;
            fout = fopen(filename.c_str(),"w");
            i++;
        }

        fputs(input.c_str(),fout);
        fputs("\n",fout);
    }
    fclose(fout);

    cout << i << endl;
    for(j = 0; j < i; j++){
        s = to_string(j);
        filename = name + s + end;
        filename2 = name + s + end2;
        commandname = "./jgraph/jgraph -P " + filename + " | ps2pdf - | convert -density 300 - -quality 100 " + filename2;
        cout << commandname << endl;
        system(commandname.c_str());
    }

    return i;
}