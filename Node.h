/*
Archive: node.h
Author: Diego Fabián Ledesma Motta
code: 1928161
email: diego.ledesma@correounivalle.edu.co
*/

#ifndef NODE_HH
#define NODE_HH

#include <vector>
//#include "string.h"

class Node {
    private:
        Node * father;
        int motherOp;
        int depth;
        int cost;

        int robotsPosition [2];
        int shipsFuel[2];
        bool foundItems [2];
        bool usingShip [2];

        static int map[10][10];
        static int itemPositions[2][2];
        static int costsArray[7];

        static int MaxDeepth; //pending
   
    public:     
        Node(Node * father, int motherOp, int depth, int cost, int robotsPosition[2], 
            int shipsFuel[2], bool foundItems[2], bool usingShip[2]);

        Node* getFather();
        int getMotherOp();
        int getDepth();
        int getCost();

        void showValues();

        bool goalReached();

        void setMap(int map[10][10]);
        void showMap();
        
        bool isPossible(int movement);

        Node partialExpansion (int op);
};

#else
class Node;
#endif
