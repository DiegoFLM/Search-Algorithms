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
    showVals2(nodeRegistry);
    */

    if (_node->goalReached()){
        victory = true;
        std::cout << "GOAL REACHED!" << std::endl;
    
        std::cout << "victory depth:    " << _node->getDepth() << std::endl;
        std::cout << "l.size():     " << l.size() << std::endl;

        std::cout << "root nodes father: " << nodeRegistry.front().getFather() << std::endl;
        printWay(_node);
        return victory;
    }


    for(int direction = 0; direction < 4; direction++){
        std::cout << "l.size():     " << l.size() << std::endl;
        //l.front()->showValues();
        //std::cout << "l.size():     " << l.size() << std::endl;
        std::cout << "is possible (" << direction << "): " << l.front()->isPossible(direction) 
        << std::endl;

        if (_node->getDepth() > 0){
            if ( (_node->getFoundItems0() == (_node->getFather())->getFoundItems0())
                && (_node->getFoundItems1() == (_node->getFather())->getFoundItems1())
                && ( std::abs(direction - _node->getMotherOp()) == 2 ) 
                && ( direction != _node->getMotherOp() )  ) {
                std::cout << "FUCKING WORKING NOT GOING BACK!!" << std::endl;
                continue;   
            }
        }

        if (l.front()->isPossible(direction)){
            nodeRegistry.push_back(((*_node).partialExpansion(direction)));
            l.push_back(&(nodeRegistry.back()));

            std::cout << std::endl << "FOR CYCLE EXPANSION0( "<< direction <<" )" << std::endl;
            std::cout << std::endl << std::endl;
        } else {
            std::cout << std::endl << "NOT GOING IN DIRECTION: " << direction << std::endl;
        }
        std::cout << "********************" << std::endl;
    }
    std::cout << "depth after for:    " << l.front()->getDepth() + 1 << std::endl;
    
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
    showVals2(nodeRegistry);*/
    l.pop_front();
    std::cout << "l.size():     " << l.size() << std::endl;
    std::cout << "nodeRegistry.size():     " << nodeRegistry.size() << std::endl;

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
    /*std::list <Node > l;
    l.push_front(rootNode);
    victory = false;*/
    int numberOfExpansions = 0;
    nodeRegistry.push_back(rootNode);
    std::cout << "l.size() = " << l.size() << std::endl;
    std::cout << "nodeRegistry.size() = " << nodeRegistry.size() << std::endl;

    if (nodeRegistry.front().goalReached()){
        victory = true;
        std::cout << "GOAL REACHED!" << std::endl;
        return;
    }else victory = false;

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




Node* Handler::getFront(){
    return &(nodeRegistry.front());
}


void Handler::printWay(Node *_node){
    Node * current_point = _node;
    Node * father = _node -> getFather();
    while (current_point->getDepth() != 0){
        std::cout << "************" << std::endl;
        std::cout << "depth = " << current_point->getDepth() <<std::endl;
        std::cout << "point[0] = " << current_point->getPosition0() << std::endl;
        std::cout << "point[1] = " << current_point->getPosition1() << std::endl;

        father = current_point->getFather();
        current_point = father;
    }

    std::cout << "************" << std::endl;
    std::cout << "start point: " << std::endl;
    std::cout << "************" << std::endl;
    std::cout << "depth = " << current_point->getDepth() <<std::endl;
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

void Handler::showVals2(std::list<Node> lst){
    std::list<Node>::iterator it;
    for (it = lst.begin(); it != lst.end(); ++it)
        (*it).showValues();
    std::cout << '\n';
}
