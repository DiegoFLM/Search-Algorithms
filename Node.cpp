#include <iostream>

#include "Node.h"


//constructor

Node::Node(int _robotsPosition[2], int _shipsFuel[2]){}


int Node::map [10][10];

void Node::setMap(int _map[10][10]){
    for (int r = 0; r < 10; r++){
        for (int c = 0; c < 10; c++){
            Node::map[r][c] = _map[r][c];
        }
    }
    /*int g = 0;
    map[0][0] = 2;*/
}


bool Node::goalReached(){
    //if (foundItems[0] && foundItems[1]) return true;
    return false;
}

/*movement operator: 
0 := up
1 := left
2 := down
3 := right*/
/*Node* Node::move (int op){
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

}*/



void Node::testMap(){
    for (int a = 0; a < 10; a ++){
        for(int b = 0; b < 10; b++){
            std::cout << Node::map[a][b] << " ";
        }
        std::cout << std::endl;
    }
}


bool Node::isPossible(int op){
    //std::cout << *((Node::map+2*10)+1);
    return true;
}





