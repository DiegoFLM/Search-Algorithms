#include <iostream>
#include <fstream>
#include <string>
 
#include <stdio.h>
#include <stdlib.h>

using namespace std;



int const L = 10;

//Map of the labyrinth without robots position 
int map[L][L] ={{0, 0, 0, 0, 0, 5, 1, 1, 4, 0},
                {0, 1, 1, 1, 1, 0, 1, 1, 1, 0},
                {0, 0, 0, 6, 6, 0, 0, 0, 0, 0},
                {1, 6, 1, 1, 1, 1, 0, 1, 1, 6},
                {1, 6, 1, 1, 1, 1, 0, 1, 1, 6},
                {1, 6, 1, 0, 0, 0, 0, 0, 0, 3},
                {1, 6, 1, 0, 1, 1, 1, 1, 0, 1},
                {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 1, 0, 1, 0, 1, 1, 1, 1},
                {1, 0, 0, 0, 6, 6, 6, 0, 0, 5},
                };



void printMap (int mapa [L][L]);
void move (int op, int pos[1][2]);

int main() {
   


    printMap(map);
}



void printMap (int mapa [L][L]){
    for (int a = 0; a < L; a ++){
        for(int b = 0; b < L; b++){
            cout << mapa[a][b] << " ";
        }
    cout << endl;
    }
}

void move (int op, int pos[1][2]){
    
}





 /*
    int array1[5];
    int s = sizeof(array1)/sizeof(int);
    fill(array1, array1 + s, 0);
    cout << sizeof(array1)/sizeof(int) << endl << s << endl;
    */
    //const size_t L = 10;
    
    //int mapSize = sizeof(map)/sizeof(int[1]);
    //cout << mapSize << endl;

    //fill(*map, *map + L * L, 0);