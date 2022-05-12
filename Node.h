/*
Archive: node.h
Author: Diego Fabián Ledesma Motta
code: 1928161
email: diego.ledesma@correounivalle.edu.co
*/

#ifndef NODE_HH
#define NODE_HH

#include <vector>

/*struct position{
    int file;
    int row;
};*/

class Node {
    private:
        Node * father;

        int robotsPosition [2];
        int shipFuel1, shipFuel2;
        bool foundItems [2];
        bool usingShip [2];

        std::vector<int> robotPositionVec;

        std::vector<std::vector<int>> knownBoxes;   


        int rowRobot;
        int columnRobot;


    public:
        /*Node( int* robotsPos [2], Node * fathersReff, int fuel1, int fuel2, 
                bool* fItems [2], bool* drivingShip [2]);*/

        /*Node(int* robotsPos, int fuel1, int fuel2, bool fItems[2], 
        bool drivingShip[2]);*/
        /*Node(int* robotsPos, int fuel1, int fuel2, 
        bool* fItems, bool * drivingShip);*/

        //Node(std::vector <int> robotsPos);

        //Node(position robotsPos);

        Node(int rowRobotP, int columnRobotP);

        bool goalReached();

        //Node* move (int op);

        //Revisar: Los atts no deben ser publicc.
        static int * map;

        //void setMap(int *mappa);
        //void testMap();
        
        bool isPossible(int op);
        
        
};
#else
class Node;
#endif
