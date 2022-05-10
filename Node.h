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
        int shipFuel1, shipFuel2;
        bool foundItems [2];
        bool usingShip [2];

        std::vector<std::vector<int>> knownBoxes;
        
    public:
        Node(Node * fathersReff, int* robotsPos [2], int fuel1, int fuel2, 
                bool* fItems [2], bool* drivingShip [2]);

        bool goalReached();
        Node* move (int op);

        

        bool isPossible(int op);
        
};
#else
class Individuo;
#endif
