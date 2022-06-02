/*
Archive: node.h
Author: Diego Fabián Ledesma Motta
code: 1928161
email: diego.ledesma@correounivalle.edu.co
*/

#include <list>
#include <iterator>

#ifndef NODE_HH
#define NODE_HH


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
        Node* autoRef;

        static int map[10][10];
        static int itemPositions[2][2];
        static int costsArray[7];

        //static int tPosition[2];
        static bool tFoundItems[2];

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

        void setTPosition();
        bool* getFoundItems();

        bool equivState0 (Node* _node2);

        int getPosition0();
        int getPosition1();
        bool getFoundItems0();
        bool getFoundItems1();
};

#else
class Node;
#endif
