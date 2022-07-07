#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "Handler.h"

int const L = 10;

/*
0 si es una casilla libre
1 si es un muro
2 si el punto de inicio
3 si es la nave 1
4 si es la nave 2
5 si es un ítem
6 si es una casilla con aceite
*/

/*int map[L][L] ={{0, 0, 0, 0, 0, 5, 1, 1, 4, 0},
                {0, 1, 1, 1, 1, 0, 1, 1, 1, 0},
                {0, 0, 0, 6, 6, 0, 0, 0, 0, 0},
                {1, 6, 1, 1, 1, 1, 0, 1, 1, 6},
                {1, 6, 1, 1, 1, 1, 0, 1, 1, 6},
                {1, 6, 1, 0, 0, 0, 0, 0, 0, 3},
                {1, 6, 1, 0, 1, 1, 1, 1, 0, 1},
                {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 1, 0, 1, 0, 1, 1, 1, 1},
                {1, 0, 0, 0, 6, 6, 6, 0, 0, 5},
                };*/

void printMap(int mappa[L][L]);

int * getLocation (int map[L][L]);

void showlist(std::list<int> g);

int main() {
    std::string rawPosition;

    std::ifstream mapFile;
    mapFile.open("map.txt"/*, std::ios::in*/);


    int readMap[L][L];
    int initialRobotsPosition[2];

    for (int r = 0; r < 10; r++){
        for (int c = 0; c < 10; c++){
            mapFile >> rawPosition;
            readMap[r][c] = std::stoi(rawPosition);

            if ( readMap[r][c] == 2 ){
                initialRobotsPosition[0] = r;
                initialRobotsPosition[1] = c;
            }
        }
    }

    int shipsFuel [2];
    shipsFuel[0] = 10;
    shipsFuel[1] = 20;
    bool foundItems[2] = {false, false};
    bool drivingShip[2] = {false, false};

    Node nod((Node *)nullptr, -1, 0, 0, initialRobotsPosition, shipsFuel, foundItems,  
            drivingShip);

    nod.setMap(readMap);
    

    std::cout << std::endl << std::endl;
    /*movement number: 
    0 := up
    1 := left
    2 := down
    3 := right*/

    Handler hand = Handler(nod);    

    auto timePoint1 = std::chrono::high_resolution_clock::now();

    /*
    0 := Breadth first search
    1 := Uniform cost search
    2 := Depth first search
    3 := Greedy search
    4 := A* search
    */
    hand.search(0);

    auto timePoint2 = std::chrono::high_resolution_clock::now();
    auto timePeriod = std::chrono::duration_cast<std::chrono::microseconds> 
                        (timePoint2 - timePoint1);
    std::cout << "search time [micro s]:  " << timePeriod.count() << std::endl;

    std::cout << "search time (from handler) [micro s]:  " << hand.getSolutionTime() << std::endl;

    /*for (int c = 0; c < hand.getVictorySize(); c++){
        std::cout << " 0000000000000000000000000000000 " << std::endl;
        std::cout << "cost: " << hand.getVicWayNode(c)->getCost() << std::endl;
        std::cout << "depth: " << hand.getVicWayNode(c)->getDepth() << std::endl;
        std::cout << "row:    " << hand.getVicWayNode(c)->getPosition0() << std::endl;
        std::cout << "column: " << hand.getVicWayNode(c)->getPosition1() << std::endl;
    }*/

   mapFile.close();
}


void printMap(int mappa[L][L]){
    for (int a = 0; a < L; a ++){
        for(int b = 0; b < L; b++){
            std::cout << mappa[a][b] << " ";
        }
        std::cout << std::endl;
    }
}


void showlist(std::list<int> g){
    std::list<int>::iterator it;
    for (it = g.begin(); it != g.end(); ++it)
        std::cout << '\t' << *it;
    std::cout << '\n';
}


