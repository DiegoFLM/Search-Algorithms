#include "Node.h"


/*¿Cómo inicializar un int array a partir de un puntero a int array?*/
//Constructor

Node::Node(Node * fatherReff, int* robotsPos [2], int fuel1, int fuel2, 
        bool* fItems [2], bool * drivingShip[2]): father(fatherReff), 
        robotsPosition({(*robotsPos)[0], (*robotsPos)[1]}),
        shipFuel1(fuel1), shipFuel2(fuel2){
    foundItems[0] = (*fItems)[0];
    foundItems[1] = (*fItems)[1];
    usingShip[0] = (*drivingShip)[0];
    usingShip[1] = (*drivingShip)[1]; 
}


bool Node::goalReached(){
    if (foundItems[0] && foundItems[1]) return true;
    return false;
}

/*movement operator: 
0 := up
1 := left
2 := down
3 := right*/
Node* Node::move (int op){
    switch(op){
        case 0:
            robotsPosition[0] += 1;
            break;
        case 1:
            robotsPosition[1] += -1;
            break;
        case 2:
            robotsPosition[0] += -1;
            break;           
        case 3:
            robotsPosition[1] += 1;
            break;
    }

}


bool Node::isPossible(int op){
    
}





