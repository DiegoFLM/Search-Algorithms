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
void printMap(int *mappa);


int main() {
    //printMap((int *)map);
    
    //Node *nullNode;
    //nullNode = nullptr;
    int initialRobotPosition[2];
    initialRobotPosition[0] = 2;
    initialRobotPosition[1] = 2;

    int fuelShip1 = 10;
    int fuelShip2 = 20;
    bool foundItems[2] = {false, false};
    bool drivingShip[2] = {false, false};

    int* initPtr = (int *)initialRobotPosition;
    bool* foundPtr = (bool *)foundItems;
    bool* drivingPtr = (bool *)drivingShip; 

    /*Node node((int *)initialRobotPosition, fuelShip1, fuelShip2, 
                (bool *)foundItems, (bool *)drivingShip);*/
    /*Node node(initPtr, fuelShip1, fuelShip2, 
                foundPtr, drivingPtr);*/
    /*Node node(initialRobotPosition, fuelShip1, fuelShip2, 
                foundItems, drivingShip);*/

    //std::vector <int> initialRobotPositionVec = {2,2};
    //std::vector <int> *vecPtr = &initialRobotPositionVec;

    Node nod(2, 2);
    //Node node(vecPtr);

    //node.setMap((int *)map);
    //node.testMap();
}

void printMap(int *mappa){

    for (int a = 0; a < L; a ++){
        for(int b = 0; b < L; b++){
            std::cout << *((mappa+a*L)+b) << " ";
        }
        std::cout << std::endl;
    }
}







