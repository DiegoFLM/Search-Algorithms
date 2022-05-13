#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "Node.h"

int const L = 10;


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


int main() {

    //printMap(map);
    
    //Node *nullNode;
    //nullNode = nullptr;
    int initialRobotPosition[2] = {2, 2};

    int fuelShip1 = 10;
    int fuelShip2 = 20;
    int shipsFuel [2]= {10, 20};
    bool foundItems[2] = {false, false};
    bool drivingShip[2] = {false, false};



    Node nod(initialRobotPosition, shipsFuel);

    nod.setMap(map);
    nod.testMap();

}


void printMap(int mappa[L][L]){
    for (int a = 0; a < L; a ++){
        for(int b = 0; b < L; b++){
            std::cout << mappa[a][b] << " ";
        }
        std::cout << std::endl;
    }
}







