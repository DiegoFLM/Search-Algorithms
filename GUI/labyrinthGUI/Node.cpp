#include <iostream>

#include "Node.h"


//constructor

Node::Node(Node * _father, int _motherOp, int _depth, int _cost, int _robotsPosition[2], 
            int _shipsFuel[2], bool _foundItems[2], bool _usingShip[2]):
            father(_father), motherOp(_motherOp), depth(_depth), cost(_cost),
            robotsPosition({_robotsPosition[0], _robotsPosition[1]}),
            shipsFuel({_shipsFuel[0], _shipsFuel[1]}),
            foundItems({_foundItems[0], _foundItems[1]}), 
            usingShip({_usingShip[0], _usingShip[1]}) {
                this->showValues();
                std::cout << "CREATING NODE WITH: " << std::endl;
                std::cout << "_shipsFuel[0] = " << _shipsFuel[0] << std::endl;
                std::cout << "_shipsFuel[1] = " << _shipsFuel[1]  << std::endl;
                std::cout << "shipsFuel[0] = " << shipsFuel[0] << std::endl;
                std::cout << "shipsFuel[1] = " << shipsFuel[1]  << std::endl;
            }

int Node::map [10][10];
int Node::itemPositions [2][2];
int Node::costsArray[7];


Node* Node::getFather(){
    return father;
}

int Node::getMotherOp(){
    return motherOp;
}

int Node::getDepth() {
    return depth;
} 

int Node::getCost() {
    return cost;
} 

void Node::showValues(){
    std::cout << "------VALUES------" << std::endl;
    std::cout << "motherOp: " << motherOp << std::endl;
    std::cout << "depth: " << depth << std::endl;
    std::cout << "cost: " << cost << std::endl;
    std::cout << "h(): " << h() << std::endl;
    std::cout << "robotsPosition[0]: " << robotsPosition[0] << std::endl;
    std::cout << "robotsPosition[1]: " << robotsPosition[1] << std::endl;
    std::cout << "shipsFuel[0]: " << shipsFuel[0] << std::endl;
    std::cout << "shipsFuel[1]: " << shipsFuel[1] << std::endl;
    std::cout << "foundItems[0]: " << foundItems[0] << std::endl;
    std::cout << "foundItems[1]: " << foundItems[1] << std::endl;
    std::cout << "usingShip[0]: " << usingShip[0] << std::endl;
    std::cout << "usingShip[1]: " << usingShip[1] << std::endl;
    std::cout << "itemPositions[0][0]: " << itemPositions[0][0] << std::endl;
    std::cout << "itemPositions[0][1]: " << itemPositions[0][1] << std::endl;
    std::cout << "itemPositions[1][0]: " << itemPositions[1][0] << std::endl;
    std::cout << "itemPositions[1][1]: " << itemPositions[1][1] << std::endl;
}

void Node::setMap(int _map[10][10]){

    int item = 0;

    for (int r = 0; r < 10; r++){
        for (int c = 0; c < 10; c++){
            map[r][c] = _map[r][c];

            if ( map[r][c] == 5 ){
                itemPositions[item][0] = r;
                itemPositions[item][1] = c;
                item++;
            } else if( map[r][c] == 2 ){
                robotsPosition[0] = r;
                robotsPosition[1] = c;
            }
        }
    }

    //Set item and ship positions 
    /*int item = 0;
    for (int r = 0; r < 10; r++){
        for (int c = 0; c < 10; c++){
            if ((map[r][c] == 5)){
                itemPositions[item][0] = r;
                itemPositions[item][1] = c;
                item++;
            }
        }
    }*/

    //setShipsPosition

    
    //costs
    costsArray[0]= 1;   //Free block
    costsArray[1]= 1000;//Obstacle
    costsArray[2]= 1;   //Initial position of the robot.
    costsArray[3]= 1;   
    costsArray[4]= 1;
    costsArray[5]= 1;
    costsArray[6]= 4;   //Unless a ship is being used.
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
Node Node::partialExpansion (int op){
    int sonsModerOp = op;
    int sonsDepth = depth + 1;

    int sonsCost;

    int sonsRobotsPosition [2];
    int sonsShipsFuel [2];
    bool sonsFoundItems [2];
    bool sonsUsingShip [2];


    switch(op){
        case 0: //Up
            sonsRobotsPosition[0] = robotsPosition[0] - 1;
            sonsRobotsPosition[1] = robotsPosition[1];
            break;
        case 1: //Left
            sonsRobotsPosition[0] = robotsPosition[0];
            sonsRobotsPosition[1] = robotsPosition[1] - 1;
            break;
        case 2: //Down
            sonsRobotsPosition[0] = robotsPosition[0] + 1;
            sonsRobotsPosition[1] = robotsPosition[1];
            break;           
        case 3: //Right
            sonsRobotsPosition[0] = robotsPosition[0];
            sonsRobotsPosition[1] = robotsPosition[1] + 1;
            break;
    }

    //sonsCost if using (or not) ship and stepping into oil:
    if (usingShip[0] || usingShip[1]){
        sonsCost = cost + 1;
    }else{
        sonsCost = cost + costsArray[map[sonsRobotsPosition[0]][sonsRobotsPosition[1]]];
    }

    

    //sonsFoundItems:  
    sonsFoundItems[0] = foundItems[0];
    sonsFoundItems[1] = foundItems[1];
    if (sonsRobotsPosition[0] == itemPositions[0][0] 
        && sonsRobotsPosition[1] == itemPositions[0][1]){
        sonsFoundItems[0] = true;
    }else if (sonsRobotsPosition[0] == itemPositions[1][0] 
        && sonsRobotsPosition[1] == itemPositions[1][1]){
        sonsFoundItems[1] = true;
    }

    //sonsShipsFuel [2]; sonsUsingShip[2]
    sonsShipsFuel[0] = shipsFuel[0];
    sonsShipsFuel[1] = shipsFuel[1];
    sonsUsingShip[0] = usingShip[0];
    sonsUsingShip[1] = usingShip[1];

    if (usingShip[0]){
        sonsShipsFuel[0] = shipsFuel[0] - 1;
        if (sonsShipsFuel[0] == 0){
            sonsUsingShip[0] = false;
        }
    }
    if (usingShip[1]){
        sonsShipsFuel[1] = shipsFuel[1] - 1;
        if (sonsShipsFuel[1] == 0){
            sonsUsingShip[1] = false;
        }
    }

    //Getting ship1?
    if (map[sonsRobotsPosition[0]][sonsRobotsPosition[1]] == 3 && shipsFuel[0] > 0 
        && !usingShip[1]){
        sonsUsingShip[0] = true;

    //Getting ship2?
    }else if (map[sonsRobotsPosition[0]][sonsRobotsPosition[1]] == 4 && shipsFuel[1] > 0
        && !usingShip[0]){
        sonsUsingShip[1] = true;
    }

    Node obj(&(*this), sonsModerOp, sonsDepth, sonsCost, sonsRobotsPosition, 
            sonsShipsFuel, sonsFoundItems, sonsUsingShip);

    return obj;
}



int Node::getPosition0(){
    return robotsPosition[0];
}

int Node::getPosition1(){
    return robotsPosition[1];
}

int Node::getItem0Position0(){
    return itemPositions[0][0];
}

int Node::getItem0Position1(){
    return itemPositions[0][1];
}

int Node::getItem1Position0(){
    return itemPositions[1][0];
}

int Node::getItem1Position1(){
    return itemPositions[1][1];
}


bool Node::getFoundItems0(){
    return foundItems[0];
}

bool Node::getFoundItems1(){
    return foundItems[1];
}

bool Node::getUsingShip0(){
    return usingShip[0];
}

bool Node::getUsingShip1(){
    return usingShip[1];
}

/*if node robots are in the same position, and have found the same item, none or both, they're 
equivState0   */   
bool Node::equivState0 (Node *_node2){
    if (  robotsPosition[0] == _node2->getPosition0()
            &&  robotsPosition[1] == _node2->getPosition1()
            &&  foundItems[0] == _node2->getFoundItems0()
            &&  foundItems[1] == _node2->getFoundItems1()){
        /*std::cout << "robotsPosition[0] = " << robotsPosition[0] << std::endl;
        std::cout << "_node2->getPosition0() = " << _node2->getPosition0() << std::endl;
        std::cout << "robotsPosition[1] = " << robotsPosition[1] << std::endl;
        std::cout << "_node2->getPosition1() = " << _node2->getPosition1() << std::endl;*/
        std::cout << "Estamos true" << std::endl;
        
        return true;
    }else {
        /*std::cout << "robotsPosition[0] = " << robotsPosition[0] << std::endl;
        std::cout << "_node2->getPosition0() = " << _node2->getPosition0() << std::endl;
        std::cout << "robotsPosition[1] = " << robotsPosition[1] << std::endl;
        std::cout << "_node2->getPosition1() = " << _node2->getPosition1() << std::endl;*/
        std::cout << "Estamos false" << std::endl;
        return false;
    }
}


int Node::h(){
    int distBetweenItems;
    int distToItem0;
    int distToItem1;
    int h;
    
    if ( !foundItems[0] && !foundItems[1] ){ // ningún item encontrado
        distBetweenItems = std::abs(itemPositions[0][0] - itemPositions[1][0])
            + std::abs(itemPositions[0][1] - itemPositions[1][1]);
        distToItem0 = std::abs(itemPositions[0][0] - robotsPosition[0])
            + std::abs(itemPositions[0][1] - robotsPosition[1]);
        distToItem1 = std::abs(itemPositions[1][0] - robotsPosition[0])
            + std::abs(itemPositions[1][1] - robotsPosition[1]);
    
        if (distToItem0 < distToItem1 )
            h = distToItem0 + distBetweenItems;
        else 
            h = distToItem1 + distBetweenItems;

        return h;
    } else if (foundItems[0]){ //first item already found
        distToItem1 = std::abs(itemPositions[1][0] - robotsPosition[0])
            + std::abs(itemPositions[1][1] - robotsPosition[1]);
        
        h = distToItem1;
        return h;
    } else { // second item already found
        distToItem0 = std::abs(itemPositions[0][0] - robotsPosition[0])
            + std::abs(itemPositions[0][1] - robotsPosition[1]);
        
        h = distToItem0;
        return h;
    } 

    std::cout << "h() OF A VICTORY NODE:" << std::endl;
    return 0;
}



