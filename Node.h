/*
Archive: node.h
Author: Diego Fabián Ledesma Motta
code: 1928161
email: diego.ledesma@correounivalle.edu.co
*/

#ifndef NODE_HH
#define NODE_HH

#include <vector>

class Node {
    private:
        Node * father;

        int robotsPosition [2];
        int shipsFuel[2];
        bool foundItems [2];
        bool usingShip [2];

        static int map[10][10];


        std::vector<std::vector<int>> knownBoxes;   


    public:
        
        Node(int robotsPosition[2], int shipsFuel[2]);

        bool goalReached();

        //Node* move (int op);

        //Revisar: Los atts no deben ser publicc.

        void setMap(int map[10][10]);
        //void setMap(int *mappa);
        void testMap();
        
        bool isPossible(int op);
        
        
};
#else
class Node;
#endif
