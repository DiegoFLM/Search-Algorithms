#include "Handler.h"

#include <iostream>


//constructor
Handler::Handler(Node _rootNode): rootNode(_rootNode){
    std::list <Node> nodeRegistry;
    Node nod555 = _rootNode;
    nodeRegistry.push_back(rootNode);
    //std::cout << "rootNode: robotsPosition[0] = " << nodeRegistry.back().getPosition0() << std::endl;
    l.push_front(&rootNode);
    victory = false;
    minCost = 0;
/*    int dir = 0;
    std::cout << "isPossible(" << dir << "): " << l.back()->isPossible(dir) 
        << std::endl;*/
    
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
    

    victory = false;
}

//best node expansion for breadthFirstSearch and uniformCostSearch
//expansion0 avoids going back.
bool Handler::expansion0(Node* _node){
    //Node * currentNode = _node;
    //Node copy = (*_node);
    //Node* _node = (Node *)&(*nodeRegistry.begin());
    /*
    std::cout << "********************" << std::endl;
    std::cout << "********************" << std::endl;
    std::cout << "***ALL ITEMS IN NodeRegistry before FOR cycle:***" << std::endl;
    std::cout << "********************" << std::endl;
    std::cout << "nodeRegistry.size(): " << nodeRegistry.size() << std::endl;
    showValsNodeRegistry(nodeRegistry);
    */

    if (_node->goalReached()){
        victory = true;
        std::cout << "GOAL REACHED!" << std::endl;
        std::cout << "victory depth:    " << _node->getDepth() << std::endl;
        std::cout << "l.size():     " << l.size() << std::endl;
        
        printWay(_node);
        std::cout << "root nodes father: " << nodeRegistry.front().getFather() << std::endl;
        return victory;
    }

    for(int direction = 0; direction < 4; direction++){
        std::cout << "l.size():     " << l.size() << std::endl;
        std::cout << "is possible (" << direction << "): " << _node->isPossible(direction) 
        << std::endl;

        if ( !(_node->isPossible(direction)) ){
            std::cout << std::endl << "NOT GOING IN DIRECTION: " << direction << std::endl;
            std::cout << "********************" << std::endl;
            continue;

        }else if (_node->getDepth() > 0){ //Not going back
            
            if ( ( _node->getFoundItems0() == (_node->getFather())->getFoundItems0() )
                && ( _node->getFoundItems1() == (_node->getFather())->getFoundItems1() )
                && ( std::abs(direction - _node->getMotherOp()) == 2 ) 
                && ( _node->getUsingShip0() ==  (_node->getFather())->getUsingShip0() )
                && ( _node->getUsingShip1() ==  (_node->getFather())->getUsingShip1() )
                ) {
                std::cout << "NOT GOING BACK UNLESS TAKING OR LEAVING A SHIP!!" << std::endl;
                continue;   
            }
        }
             //is possible to expand into the current direction

        nodeRegistry.push_back(((*_node).partialExpansion(direction)));
        l.push_back(&(nodeRegistry.back()));

        std::cout << std::endl << "FOR CYCLE EXPANSION0( "<< direction <<" )" << std::endl;
        std::cout << std::endl << std::endl;
        
    }
    std::cout << "depth after for:    " << l.back()->getDepth() << std::endl;
    
    /*std::cout << "********************" << std::endl;
    std::cout << "******END FOR*******" << std::endl;
    std::cout << "********************" << std::endl;
    std::cout << "***ALL ITEMS IN L***" << std::endl;
    std::cout << "****BEFORE POP*******" << std::endl;
    showValsL(l);
    std::cout << "********************" << std::endl;
    std::cout << "********************" << std::endl;
    std::cout << "***ALL ITEMS IN NodeRegistry after FOR cycle***" << std::endl;
    std::cout << "********************" << std::endl;
    showValsNodeRegistry(nodeRegistry);*/
    
    
    //l.pop_front();
    l.remove(_node);
    
    
    std::cout << "l.size() after l.remove(_node) :    " << l.size() << std::endl;
    std::cout << "nodeRegistry.size() at the end of expansion0: " << nodeRegistry.size() << std::endl;

    return victory;
}

//best node expansion for depthFirstSearch.
//expansion2 avoids going back and cycles.
bool Handler::expansion2(Node* _expNode){
    
    Node* ancestor;

    if (_expNode->goalReached()){
        victory = true;
        std::cout << "GOAL REACHED!" << std::endl;
        std::cout << "victory depth:    " << _expNode->getDepth() << std::endl;
        std::cout << "l.size():     " << l.size() << std::endl;
        std::cout << "root nodes father: " << nodeRegistry.front().getFather() << std::endl;
        printWay(_expNode);
        return victory;
    }

    //Avoid cycles. If it takes a ship or not, that's ignored since cost is not
    //relevant for depthFirstSearch() nor for greedySearch()
    if ( _expNode->getDepth() > 1 ){
        std::cout << "ENTERED INSIDE IF OF ANCESTOR: " << std::endl;
        ancestor = _expNode->getFather();
        while ( !(ancestor->getFather() == nullptr) ){
            if( (ancestor->getPosition0() == _expNode->getPosition0() )
                && ( ancestor->getPosition1() == _expNode->getPosition1() )
                && ( ancestor->getFoundItems0() == _expNode->getFoundItems0() )
                && ( ancestor->getFoundItems1() == _expNode->getFoundItems1() )  
                /* && !( ancestor->getUsingShip0() == 0  &&  _expNode->getUsingShip0() == 1 )
                && !( ancestor->getUsingShip1() == 0  &&  _expNode->getUsingShip1() == 1 )  */
                )
            {
                std::cout << "***AVOIDING CYCLES WORKING***" << std::endl;
                
                l.remove(_expNode);
    
                std::cout << "l.size() after l.remove(_expNode) :    " << l.size() << std::endl;
                std::cout << "nodeRegistry.size() at the end of expansion0: " << nodeRegistry.size() << std::endl;
                std::cout << "EXITING WHILE OF ANCESTORS: " << std::endl;
                return victory;
            }
            /*std::cout << "CHANGE OF ANCESTOR: " << std::endl;
            std::cout << "ancestor->showValues()  BEFORE change: " << std::endl;
            ancestor->showValues();*/

            ancestor = ancestor->getFather();
            
            //std::cout << "ancestor->showValues()  AFTER change: " << std::endl;
            //ancestor->showValues();
        }
        
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
                && ( _expNode->getUsingShip0() == (_expNode->getFather())->getUsingShip0() )
                && ( _expNode->getUsingShip1() == (_expNode->getFather())->getUsingShip1() )
                ) {
                std::cout << "NOT GOING BACK UNLESS TAKING OR LEAVING A SHIP" << std::endl;
                continue;   
            }

            
        }

        nodeRegistry.push_back(((*_expNode).partialExpansion(direction)));
        l.push_back(&(nodeRegistry.back()));
        
        std::cout << std::endl << "FOR CYCLE EXPANSION0( "<< direction <<" )" << std::endl;
        std::cout << std::endl << std::endl;
    
    } // end for
    
    std::cout << "depth after for:    " << l.back()->getDepth() << std::endl;
    
    l.remove(_expNode);
    
    std::cout << "l.size() after l.remove(_expNode) :    " << l.size() << std::endl;
    std::cout << "nodeRegistry.size() at the end of expansion0: " << nodeRegistry.size() << std::endl;

    return victory;
} 


void Handler::search(int mode){
        /*
    0 := Breadth first search
    1 := Uniform cost search
    */
    switch (mode)
    {
    case 0:
        breadthFirstSearch();
        break;
    
    default:
        break;
    }
}




void Handler::breadthFirstSearch(){

    l.clear();
    l.push_front(&rootNode);
    victory = false;

    
    int numberOfExpansions = 0;
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
        numberOfExpansions++;
        std::cout << "Number of expansions: " << numberOfExpansions << std::endl;
        //l.front()->showValues();
    }

    //nodeRegistry.back().showValues();
    //l.front()->showValues();
    /*std::cout << "********************" << std::endl;
    expansion0(l.front());
    l.front()->showValues();
    
    std::cout << "********************" << std::endl;
    expansion0(l.front());
    l.front()->showValues();
    std::cout << "********************" << std::endl;
    expansion0(l.front());
    
    l.front()->showValues();
    std::cout << "********************" << std::endl;
    std::cout << l.size() << std::endl;*/
}


void Handler::uniformCostSearch(){
    l.clear();
    l.push_front(&rootNode);
    victory = false;
    minCost = 0;

    int numberOfExpansions = 0;
    nodeRegistry.push_back(rootNode);

    std::cout << "l.size() = " << l.size() << std::endl;

    if (nodeRegistry.back().goalReached()){
        victory = true;
        std::cout << "GOAL REACHED!" << std::endl;
        return;
    }

    while(!victory /*&& (numberOfExpansions != 4)*/)
    {
        //std::cout << std::endl << "l.front()->showValues() before expansion: " << std::endl;
        //l.front()->showValues();
        std::cout << std::endl;

        minCost = l.front()->getCost();
        Node* expandingNode = l.front();
        std::list<Node *>::iterator it;
        for (it = l.begin(); it != l.end(); ++it){
            //std::cout << "(*it)->getCost() = " << (*it)->getCost() << std::endl;
            if( (*it)->getCost() < minCost ){
                minCost = (*it)->getCost();
                expandingNode = *it;
            }
        }
        std::cout << std::endl << "********************" << std::endl;
        std::cout << std::endl << "********************" << std::endl;
        std::cout << "expandingNode: " << std::endl;
        expandingNode->showValues();


        expansion0(expandingNode);
        numberOfExpansions++;
        std::cout << "Number of expansions: " << numberOfExpansions << std::endl;
        //l.front()->showValues();
    }
}

void Handler::depthFirstSearch(){
    l.clear();
    l.push_front(&rootNode);
    victory = false;

    std::cout << "nodeRegistry.size() before nodeRegistry.push_back(rootNode) : " 
        << nodeRegistry.size() << std::endl << std::endl;
    int numberOfExpansions = 0;
    nodeRegistry.push_back(rootNode);
    std::cout << "nodeRegistry.size() after nodeRegistry.push_back(rootNode) : " 
        << nodeRegistry.size() << std::endl;

    while (!victory  /*&& !( numberOfExpansions == 4)*/ ){
        std::cout << std::endl << "l.back()->showValues()   : " << std::endl;
        l.back()->showValues();
        expansion2(l.back());
        numberOfExpansions++;
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
    int numberOfExpansions = 0;

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
            //(*it)->showValues();
            //std::cout << "p3" << std::endl;
            //std::cout << "(*it)->h() = " << (*it)->h() << std::endl;
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
        numberOfExpansions++;
        std::cout << "Number of expansions: " << numberOfExpansions << std::endl;
        //l.front()->showValues();
    }
}


void Handler::aAsteriscSearch(){

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
        std::cout << "point[0] = " << current_point->getPosition0() << std::endl;
        std::cout << "point[1] = " << current_point->getPosition1() << std::endl;

        father = current_point->getFather();
        current_point = father;
    }

    std::cout << "************" << std::endl;
    std::cout << "start point: " << std::endl;
    std::cout << "************" << std::endl;
    std::cout << "depth = " << current_point->getDepth() <<std::endl;
    std::cout << "h() = " << current_point->h() <<std::endl;
    std::cout << "point[0] = " << current_point->getPosition0() << std::endl;
    std::cout << "point[1] = " << current_point->getPosition1() << std::endl;
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




