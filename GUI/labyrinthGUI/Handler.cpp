#include "Handler.h"

#include <iostream>


//constructor
Handler::Handler(Node _rootNode): rootNode(_rootNode){
    std::list <Node> nodeRegistry;
    nodeRegistry.push_back(rootNode);
    l.push_front(&rootNode);
    victory = false;
    minCost = 0;

    std::vector<Node *> solutionPath;

    numberOfExpansions = 0;
    
}


Handler::Handler(Node fn, int _initialRobotPosition[2], int _shipsFuel[2], bool _foundItems[2],
                    bool _drivingShip[2]):rootNode(fn){
    
    /*Node root((Node *)nullptr, -1, 0, 0, {_initialRobotPosition[0], _initialRobotPosition[1]}, 
    {_shipsFuel[0], _shipsFuel[1]}, {_foundItems[0], _foundItems[1]}, 
            {_drivingShip[0], _drivingShip[1]});*/

    Node nod((Node *)nullptr, -1, 0, 0, _initialRobotPosition, _shipsFuel, _foundItems, 
            _drivingShip);

    std::list <Node> nodeRegistry;
    nodeRegistry.push_back(nod);
    //l.push_front(   );
    numberOfExpansions = 0;

    victory = false;
}




/*Node expansion for breadthFirstSearch
    expansion0 avoids going back regardless of wether a ship is being used or not. 
    Only going back when taking an item
    Doesn't avoid cycles. */
bool Handler::expansion0(Node* _node){

    numberOfExpansions++;

    if (_node->goalReached()){
        victory = true;
        std::cout << "GOAL REACHED!" << std::endl;
        std::cout << "victory depth:    " << _node->getDepth() << std::endl;
        std::cout << "l.size():     " << l.size() << std::endl;
        
        //printWay(_node);
        makeWay(_node);
        std::cout << "root nodes father: " << nodeRegistry.front().getFather() << std::endl;
        return victory;
    }

    for(int direction = 0; direction < 4; direction++){
        /*std::cout << "l.size():     " << l.size() << std::endl;
        std::cout << "is possible (" << direction << "): " << _node->isPossible(direction) 
        << std::endl;*/

        if ( !(_node->isPossible(direction)) ){
            std::cout << std::endl << "NOT GOING IN DIRECTION: " << direction << std::endl;
            std::cout << "********************" << std::endl;
            continue;

        }else if (_node->getDepth() > 0){ //Not going back
            
            if ( ( _node->getFoundItems0() == (_node->getFather())->getFoundItems0() )
                && ( _node->getFoundItems1() == (_node->getFather())->getFoundItems1() )
                && ( std::abs(direction - _node->getMotherOp()) == 2 ) 
                ) {
                std::cout << "NOT GOING BACK UNLESS TAKING AN ITEM!!" << std::endl;
                continue;   
            }
        }
             //is possible to expand into the current direction
        nodeRegistry.push_back( (*_node).partialExpansion(direction) );
        l.push_back(&(nodeRegistry.back()));
    }
    std::cout << "depth after for:    " << l.back()->getDepth() << std::endl;
   
    l.remove(_node);
    return victory;
}



//Node expansion for uniformCostSearch
//expansion1 avoids going back unless taking or leaving a ship or taking an item. Doesn't avoid cycles.
//Ideally, it would be able to go back when using or leaving a ship, but it takes too much time.
bool Handler::expansion1(Node* _node){

    numberOfExpansions++;

    if (_node->goalReached()){
        victory = true;
        std::cout << "GOAL REACHED!" << std::endl;
        std::cout << "victory depth:    " << _node->getDepth() << std::endl;
        std::cout << "l.size():     " << l.size() << std::endl;
        
        //printWay(_node);
        makeWay(_node);
        std::cout << "root nodes father: " << nodeRegistry.front().getFather() << std::endl;
        return victory;
    }

    for(int direction = 0; direction < 4; direction++){
        /*std::cout << "l.size():     " << l.size() << std::endl;
        std::cout << "is possible (" << direction << "): " << _node->isPossible(direction) 
        << std::endl;*/

        if ( !(_node->isPossible(direction)) ){
            std::cout << std::endl << "NOT GOING IN DIRECTION: " << direction << std::endl;
            std::cout << "********************" << std::endl;
            continue;

        }else if (_node->getDepth() > 0){ //Not going back
            
            if ( ( _node->getFoundItems0() == (_node->getFather())->getFoundItems0() )
                && ( _node->getFoundItems1() == (_node->getFather())->getFoundItems1() )
                && ( std::abs(direction - _node->getMotherOp()) == 2 ) 

                //Commented comparisons are the ideal, but execution time grows too much.
                // && ( _node->getUsingShip0() == 0 && _node->getUsingShip1() == 0 )
                // && ( _node->getFather()->getUsingShip0() == 0 && _node->getFather()->getUsingShip1() == 0 )
                && ( _node->getUsingShip0() == _node->getFather()->getUsingShip0() )
                && ( _node->getUsingShip1() == _node->getFather()->getUsingShip1() )
                ) {
                std::cout << "NOT GOING BACK UNLESS TAKING OR LEAVING A SHIP OR TAKING AN ITEM!!" << std::endl;
                continue; 
            }
        }
             //is possible to expand into the current direction
        nodeRegistry.push_back( (*_node).partialExpansion(direction) );
        l.push_back(&(nodeRegistry.back()));
    }
    std::cout << "depth after for:    " << l.back()->getDepth() << std::endl;
   
    l.remove(_node);
    return victory;
}



/*Node expansion for depthFirstSearch and greedySearch
    expansion2 avoids going back and cycles regardless of 
    wether a ship is being used or not */
bool Handler::expansion2(Node* _expNode){
    
    numberOfExpansions++;

    Node* ancestor;

    if (_expNode->goalReached()){
        victory = true;
        std::cout << "GOAL REACHED!" << std::endl;
        std::cout << "victory depth:    " << _expNode->getDepth() << std::endl;
        std::cout << "l.size():     " << l.size() << std::endl;
        std::cout << "root nodes father: " << nodeRegistry.front().getFather() << std::endl;
        //printWay(_expNode);
        makeWay(_expNode);
        return victory;
    }

    //Avoid cycles. If it takes a ship or not, that's ignored since cost is not
    //relevant for depthFirstSearch() nor for greedySearch()
    if ( _expNode->getDepth() > 1 ){
        //std::cout << "ENTERED INSIDE IF OF ANCESTOR: " << std::endl;
        ancestor = _expNode->getFather();
        while ( !(ancestor->getFather() == nullptr) ){
            if(    ( ancestor->getPosition0() == _expNode->getPosition0() )
                && ( ancestor->getPosition1() == _expNode->getPosition1() )
                && ( ancestor->getFoundItems0() == _expNode->getFoundItems0() )
                && ( ancestor->getFoundItems1() == _expNode->getFoundItems1() )  
                
                )
            {
                std::cout << "***AVOIDING CYCLES WORKING***" << std::endl;
                
                numberOfExpansions--;
                l.remove(_expNode);
                return victory;
            }

            ancestor = ancestor->getFather();
        }
        
    }

    for(int direction = 3; direction >= 0; direction--){
        /*std::cout << "l.size():     " << l.size() << std::endl;
        std::cout << "is possible (" << direction << "): " << _expNode->isPossible(direction) 
        << std::endl; */  

        if ( !(_expNode->isPossible(direction)) ){
            std::cout << std::endl << "NOT GOING IN DIRECTION: " << direction << std::endl;
            std::cout << "********************" << std::endl;
            continue;
        } else if (_expNode->getDepth() > 0)    //Not going back
        { 

            if ( (_expNode->getFoundItems0() == (_expNode->getFather())->getFoundItems0())
                && (_expNode->getFoundItems1() == (_expNode->getFather())->getFoundItems1())
                && ( std::abs(direction - _expNode->getMotherOp()) == 2 ) 
                /*&& ( _expNode->getUsingShip0() == (_expNode->getFather())->getUsingShip0() )
                && ( _expNode->getUsingShip1() == (_expNode->getFather())->getUsingShip1() )*/
                ) {
                std::cout << "NOT GOING BACK" << std::endl;
                continue;   
            }
        }

        nodeRegistry.push_back(((*_expNode).partialExpansion(direction)));
        l.push_back(&(nodeRegistry.back()));
    } // end for
    
    //std::cout << "depth after for:    " << l.back()->getDepth() << std::endl;
    
    l.remove(_expNode);
    return victory;
} 




/*Node expansion for aAsteriscSearch
    Expansion3 avoids going back, however, if a ship is being used,
    it allows "going back" since fuel is finite, and this freedom can be
    helpful for finding the best way. Doesn't avoid cycles. */
bool Handler::expansion3(Node* _expNode){
    
    numberOfExpansions++;

    Node* ancestor;

    if (_expNode->goalReached()){
        victory = true;
        std::cout << "GOAL REACHED!" << std::endl;
        std::cout << "victory depth:    " << _expNode->getDepth() << std::endl;
        std::cout << "l.size():     " << l.size() << std::endl;
        std::cout << "root nodes father: " << nodeRegistry.front().getFather() << std::endl;
        //printWay(_expNode);
        makeWay(_expNode);
        return victory;
    }


    for(int direction = 3; direction >= 0; direction--){
        std::cout << "l.size():     " << l.size() << std::endl;
        std::cout << "is possible (" << direction << "): " << _expNode->isPossible(direction) 
        << std::endl;   

        if ( !(_expNode->isPossible(direction)) ){
            std::cout << std::endl << "NOT GOING IN DIRECTION: " << direction << std::endl;
            std::cout << "********************" << std::endl;
            continue;
        } else if (_expNode->getDepth() > 0)    //Not going back
        { 

            if ( (_expNode->getFoundItems0() == (_expNode->getFather())->getFoundItems0())
                && (_expNode->getFoundItems1() == (_expNode->getFather())->getFoundItems1())
                && ( std::abs(direction - _expNode->getMotherOp()) == 2 ) 
                //&& ( _expNode->getUsingShip0() == 0 && _expNode->getUsingShip1() == 0 )
                //&& ( _expNode->getFather()->getUsingShip0() == 0 && _expNode->getFather()->getUsingShip1() == 0 )

                && ( _expNode->getUsingShip0() == _expNode->getFather()->getUsingShip0() )
                && ( _expNode->getUsingShip1() == _expNode->getFather()->getUsingShip1() )

                ) {
                std::cout << "NOT GOING BACK UNLESS USING OR LEAVING A SHIP OR TAKING AN ITEM" << std::endl;
                continue;   
            }
        }

        nodeRegistry.push_back(((*_expNode).partialExpansion(direction)));
        l.push_back(&(nodeRegistry.back()));
    } // end for
    
    l.remove(_expNode);
    return victory;
} 






void Handler::search(int mode){

    auto timePoint1 = std::chrono::high_resolution_clock::now();

    /*
    0 := Breadth first search
    1 := Uniform cost search
    2 := Depth first search
    3 := Greedy search
    4 := A* search
    */
    switch (mode)
    {
    case 0:
        breadthFirstSearch();
        break;
    
    case 1:
        uniformCostSearch();
        break;

    case 2:
        depthFirstSearch();
        break;
    
    case 3:
        greedySearch();
        break;
    
    case 4:
        aAsteriscSearch();
        break;


    default:
        std::cout << "ERROR IN HANDLER::SEARCH(INT MODE)  " << std::endl;
        break;
    }

    auto timePoint2 = std::chrono::high_resolution_clock::now();
    solutionTime = std::chrono::duration_cast<std::chrono::microseconds> 
                        (timePoint2 - timePoint1);
}




void Handler::breadthFirstSearch(){

    l.clear();
    l.push_front(&rootNode);
    victory = false;

    numberOfExpansions = 0;
    nodeRegistry.push_back(rootNode);
    std::cout << "l.size() = " << l.size() << std::endl;
    std::cout << "nodeRegistry.size() = " << nodeRegistry.size() << std::endl;

    if (nodeRegistry.back().goalReached()){
        victory = true;
        std::cout << "GOAL REACHED!" << std::endl;
        return;
    }

    while(!victory /*&& (numberOfExpansions != 3)*/)
    {
        std::cout << std::endl << "l.front()->showValues()   : " << std::endl;
        l.front()->showValues();
        expansion0(l.front());
        std::cout << "Number of expansions: " << numberOfExpansions << std::endl;
    }
}


void Handler::uniformCostSearch(){
    l.clear();
    l.push_front(&rootNode);
    victory = false;
    minCost = 0;

    numberOfExpansions = 0;
    nodeRegistry.push_back(rootNode);

    std::cout << "l.size() = " << l.size() << std::endl;

    if (nodeRegistry.back().goalReached()){
        victory = true;
        std::cout << "GOAL REACHED!" << std::endl;
        return;
    }

    while(!victory /*&& (numberOfExpansions != 4)*/ )
    {
        std::cout << std::endl;

        minCost = l.front()->getCost();
        Node* expandingNode = l.front();
        std::list<Node *>::iterator it;
        for (it = l.begin(); it != l.end(); ++it){
            if( (*it)->getCost() < minCost ){
                minCost = (*it)->getCost();
                expandingNode = *it;
            }
        }
        std::cout << std::endl << "********************" << std::endl;
        std::cout << std::endl << "********************" << std::endl;
        std::cout << "expandingNode: " << std::endl;
        expandingNode->showValues();

        expansion1(expandingNode);
        std::cout << "Number of expansions: " << numberOfExpansions << std::endl;
    }
}

void Handler::depthFirstSearch(){
    l.clear();
    l.push_front(&rootNode);
    victory = false;

    std::cout << "nodeRegistry.size() before nodeRegistry.push_back(rootNode) : " 
        << nodeRegistry.size() << std::endl << std::endl;
    
    numberOfExpansions = 0;
    
    nodeRegistry.push_back(rootNode);
    std::cout << "nodeRegistry.size() after nodeRegistry.push_back(rootNode) : " 
        << nodeRegistry.size() << std::endl;

    while (!victory  /*&& !( numberOfExpansions == 4)*/ ){
        std::cout << std::endl << "l.back()->showValues()   : " << std::endl;
        l.back()->showValues();
        expansion2(l.back());
        std::cout << "Number of expansions: " << numberOfExpansions << std::endl;
    }
}



/*  greedySearch() expands nodes in the reverse order right now.
It can be modiefied to follow an operator order by doing the for loop
from the back to the front of l  */
void Handler::greedySearch(){
    l.clear();
    l.push_front(&rootNode);
    victory = false;
    int minH = 0;
    numberOfExpansions = 0;

    nodeRegistry.push_back(rootNode);

    std::cout << "l.size() = " << l.size() << std::endl;

    if (nodeRegistry.back().goalReached()){
        victory = true;
        std::cout << "GOAL REACHED!" << std::endl;
        return;
    }


    while(!victory  /* && (numberOfExpansions != 10) */  )
    {
        std::cout  << std::endl;

        minH = l.back()->h();
        //std::cout << "p2" << std::endl;
        Node* expandingNode = l.back();
        std::list<Node *>::reverse_iterator it;
        for (it = l.rbegin(); it != l.rend(); ++it){
            if( (*it)->h() < minH ){
                minH = (*it)->h();
                expandingNode = *it;
            }
        }

        std::cout << std::endl << "********************" << std::endl;
        std::cout << std::endl << "********************" << std::endl;
        std::cout << "expandingNode: " << std::endl;
        expandingNode->showValues();

        expansion2(expandingNode);
        std::cout << "Number of expansions: " << numberOfExpansions << std::endl;
    }
}


void Handler::aAsteriscSearch(){
    l.clear();
    l.push_front(&rootNode);
    victory = false;
    int minF = 0; //f = h() + cost()
    numberOfExpansions = 0;

    nodeRegistry.push_back(rootNode);

    std::cout << "l.size() = " << l.size() << std::endl;

    if (nodeRegistry.back().goalReached()){
        victory = true;
        std::cout << "GOAL REACHED!" << std::endl;
        return;
    }

    while(!victory  /* && (numberOfExpansions != 10) */  )
    {
        std::cout  << std::endl;

        minF = l.back()->h() + l.back()->getCost();
        Node* expandingNode = l.back();
        std::list<Node *>::reverse_iterator it;
        for (it = l.rbegin(); it != l.rend(); ++it){
            if( ( (*it)->h() + (*it)->getCost() ) < minF ){
                minF = (*it)->h() + (*it)->getCost();
                expandingNode = *it;
            }
        }

        std::cout << std::endl << "********************" << std::endl;
        std::cout << std::endl << "********************" << std::endl;
        std::cout << "expandingNode: " << std::endl;
        expandingNode->showValues();

        expansion3(expandingNode);
        std::cout << "Number of expansions: " << numberOfExpansions << std::endl;
    }
}



Node* Handler::getFront(){
    return &(nodeRegistry.front());
}


void Handler::printWay(Node *_node){
    Node * current_point = _node;
    Node * father = _node -> getFather();
    while (current_point->getDepth() != 0){
        std::cout << "************" << std::endl;
        std::cout << "depth = " << current_point->getDepth() <<std::endl;
        std::cout << "cost = " << current_point->getCost() <<std::endl;
        std::cout << "h() = " << current_point->h() <<std::endl;
        std::cout << "Position[0] = " << current_point->getPosition0() << std::endl;
        std::cout << "Position[1] = " << current_point->getPosition1() << std::endl;

        father = current_point->getFather();
        current_point = father;
    }

    std::cout << "************" << std::endl;
    std::cout << "start point: " << std::endl;
    std::cout << "************" << std::endl;
    std::cout << "depth = " << current_point->getDepth() << std::endl;
    std::cout << "cost = " << current_point->getCost() << std::endl;
    std::cout << "h() = " << current_point->h() <<std::endl;
    std::cout << "point[0] = " << current_point->getPosition0() << std::endl;
    std::cout << "point[1] = " << current_point->getPosition1() << std::endl;
}


void Handler::makeWay(Node* _vicNode){
    victorysize = _vicNode->getDepth() + 1;

    Node * current_point = _vicNode;
    Node * father = _vicNode -> getFather();
    
    for(int c = 0; c <= _vicNode->getDepth(); c++ ){
        std::vector<Node *>::iterator iter;
        iter = solutionPath.begin();
        solutionPath.insert(iter, current_point);

        father = current_point->getFather();
        current_point = father;
    }
}




void Handler::showValsL(std::list<Node *> lst)
{
    std::list<Node *>::iterator it;
    for (it = lst.begin(); it != lst.end(); ++it)
        (*it)->showValues();
    std::cout << '\n';
}

void Handler::showValsNodeRegistry(std::list<Node> lst){
    std::list<Node>::iterator it;
    for (it = lst.begin(); it != lst.end(); ++it)
        (*it).showValues();
    std::cout << '\n';
}

Node* Handler::getVicWayNode(int position){
    return solutionPath.at(position);
}

int Handler::getVictorySize(){
    return victorysize;
}

int Handler::getSolutionTime(){
    return solutionTime.count();
}


int Handler::getRobotsPosition0(int posNode){
    return solutionPath.at(posNode)->getPosition0();
}


int Handler::getRobotsPosition1(int posNode){
    return solutionPath.at(posNode)->getPosition1();
}

int Handler::getNumberOfExpansions(){
    return numberOfExpansions;
}
