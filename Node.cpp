#include <iostream>

#include "Node.h"


//constructor

Node::Node(Node * _father, int _robotsPosition[2], int _shipsFuel[2], bool _foundItems[2],
            bool _usingShip[2]):
            robotsPosition({_robotsPosition[0], _robotsPosition[1]}),
            shipsFuel({_shipsFuel[0], _shipsFuel[1]}),
            foundItems({_foundItems[0], _foundItems[1]}), 
            usingShip({_usingShip[0], _usingShip[1]}) {
                
            }


int Node::map [10][10];
int Node::itemPositions [2][2];

void Node::setMap(int _map[10][10]){
    for (int r = 0; r < 10; r++){
        for (int c = 0; c < 10; c++){
            Node::map[r][c] = _map[r][c];
        }
    }

    //Set item positions 
    int item = 0;
    for (int r = 0; r < 10; r++){
        for (int c = 0; c < 10; c++){
            if ((map[r][c] == 5)){
                itemPositions[item][0] = r;
                itemPositions[item][1] = c;
                item++;
            }
        }
    }
    
}


bool Node::goalReached(){
    if (foundItems[0] && foundItems[1]) return true;
    return false;
}




void Node::showMap(){
    for (int a = 0; a < 10; a ++){
        for(int b = 0; b < 10; b++){
            if (a == robotsPosition[0] && b == robotsPosition[1]){
                std::cout << 2 << " ";
            }else{
                std::cout << Node::map[a][b] << " ";
            }
        }
        std::cout << std::endl;
    }

    /*for(int z = 0; z < 2; z ++){
        for (int w = 0; w < 2; w++){
            std::cout << itemPositions[z][w] << " ";
        }
        std::cout << std::endl;
    } */ 
}

/*movement number: 
0 := up
1 := left
2 := down
3 := right*/
bool Node::isPossible(int movement){
    switch(movement){
        case 0: //up
            if(robotsPosition[0] == 0){
                return false;
            }else if (map[robotsPosition[0]-1][robotsPosition[1]] == 1){
                return false;
            }else{
                return true;
            }
            break;
        case 1: //left
            if(robotsPosition[1] == 0){
                return false;
            }else if (map[robotsPosition[0]][robotsPosition[1]-1] == 1){
                return false;
            }else{
                return true;
            }
            break;
        case 2: //down
            if(robotsPosition[0] == 9){
                return false;
            }else if (map[robotsPosition[0]+1][robotsPosition[1]] == 1){
                return false;
            }else{
                return true;
            }
            break;
        case 3: //right
            if(robotsPosition[1] == 9){
                return false;
            }else if (map[robotsPosition[0]][robotsPosition[1]+1] == 1){
                return false;
            }else{
                return true;
            }
            break;
    }
    std::cout<<"error in switch"<<std::endl;
    return false;
}


/*movement number: 
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



