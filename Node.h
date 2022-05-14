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

        static int itemPositions[2][2];

        //std::vector<std::vector<int>> knownBoxes;   


    public:
        
        Node(Node * father, int robotsPosition[2], int shipsFuel[2], bool foundItems[2],
            bool usingShip[2]);

        bool goalReached();

        void setMap(int map[10][10]);
        void showMap();
        
        bool isPossible(int movement);


        //Node* move (int op);

        
        
};
#else
class Node;
#endif
