#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "Node.h"

using namespace std;


int const L = 10;

//added
typedef int Matrix[L][L];




//Map of the labyrinth without robots position 
int map[L][L] ={{0, 0, 0, 0, 0, 5, 1, 1, 4, 0},
//Matrix map =   {{0, 0, 0, 0, 0, 5, 1, 1, 4, 0},
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
void eg2(int *mappa);
void eg2(int *mappa){
    //cout << endl << *((mappa+2*L)+3)<< endl;

    for (int a = 0; a < L; a ++){
        for(int b = 0; b < L; b++){
            cout << *((mappa+a*L)+b) << " ";
        }
        cout << endl;
    }
}

/*void eg(Matrix *mappa);
void eg(Matrix *mappa){
    cout << endl << (*mappa)[9][9]<< endl;
}*/

//void printMap (int theMap[L][L]);

int main() {
    //eg(&map);
    eg2((int *)map);

    //printMap(map);
}


/*
void printMap (int theMap [L][L]){
//void printMap (int * theMap){    

    for (int a = 0; a < L; a ++){
        for(int b = 0; b < L; b++){
            cout << theMap[a][b] << " ";
        }
    cout << endl;
    }
}
*/







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