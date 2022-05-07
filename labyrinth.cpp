#include <iostream>
#include <fstream>
#include <string>
 
#include <stdio.h>
#include <stdlib.h>

using namespace std;



void printMap (int side, int mapa [10][10]){
    for (int a = 0; a < side; a ++){
        for(int b = 0; b < side; b++){
            cout << mapa[a][b] << " ";
        }
    cout << endl;
    }
}


int main() {
    /*
    int array1[5];
    int s = sizeof(array1)/sizeof(int);
    fill(array1, array1 + s, 0);
    cout << sizeof(array1)/sizeof(int) << endl << s << endl;
    */

    const size_t L = 10;

    //Map of the labyrinth:
    int map[L][L] ={{0, 0, 0, 0, 0, 5, 1, 1, 4, 0},
                    {0, 1, 1, 1, 1, 0, 1, 1, 1, 0},
                    {0, 0, 2, 6, 6, 0, 0, 0, 0, 0},
                    {1, 6, 1, 1, 1, 1, 0, 1, 1, 6},
                    {1, 6, 1, 1, 1, 1, 0, 1, 1, 6},
                    {1, 6, 1, 0, 0, 0, 0, 0, 0, 3},
                    {1, 6, 1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 1, 0, 1, 0, 1, 1, 1, 1},
                    {1, 0, 0, 0, 6, 6, 6, 0, 0, 5},
                    };

    //int mapSize = sizeof(map)/sizeof(int[1]);
    //cout << mapSize << endl;

    //fill(*map, *map + L * L, 0);


   

    printMap(10, map);

}