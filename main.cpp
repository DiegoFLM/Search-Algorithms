#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "Node.h"

int const L = 10;

/*¿Es válido poner un 0 en la posición inicial 
y usar el 2 para representar la posición actual del robot?  */

/*
0 si es una casilla libre
1 si es un muro
2 si el punto de inicio
3 si es la nave 1
4 si es la nave 2
5 si es un ítem
6 si es una casilla con aceite
*/

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

void printMap(int mappa[L][L]);

int * getLocation (int map[L][L]){
    int loc [2];
    for (int row = 0; row < L; row++){
        for (int column = 0; column < L; column++){
            if(map[row][column] == 2){
                loc[0] = row;
                loc[1] = column;
            }
        }
    }
    return (int *)loc;
}


int main() {

    int initialRobotPosition[2] = {2,2};
    int shipsFuel [2]= {10, 20};
    bool foundItems[2] = {false, false};
    bool drivingShip[2] = {false, false};
    int itemPositions[2][2] = {{0, 5},{9, 9}};

    Node nod(nullptr, -1, 0, 0, initialRobotPosition, shipsFuel, foundItems, 
            drivingShip);

    nod.setMap(map);
    nod.showMap();
    //nod.showValues();

    /*if (!nod.isPossible(2)){
        std::cout <<"Not possible"<< std::endl;  
    } else {
        std::cout <<"Possible"<< std::endl;
    }*/

    std::cout << std::endl << std::endl;

    //Node nod2(&nod, 3, 1, 1, initialRobotPosition, shipsFuel, foundItems, drivingShip);


    /*movement number: 
    0 := up
    1 := left
    2 := down
    3 := right*/
    std::cout << "nos.ispossible(int op):  " << nod.isPossible(3) << std::endl << std::endl;

    //Node node2;
    Node node2 = nod.partialExpansion(1);
    node2.showValues();
}


void printMap(int mappa[L][L]){
    for (int a = 0; a < L; a ++){
        for(int b = 0; b < L; b++){
            std::cout << mappa[a][b] << " ";
        }
        std::cout << std::endl;
    }
}







