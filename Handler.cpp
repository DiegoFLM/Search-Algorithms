#include "Handler.h"

#include <iostream>


//constructor
Handler::Handler(Node _rootNode): rootNode(_rootNode){
    std::list <Node> nodeRegistry;
    Node nod555 = _rootNode;
    nodeRegistry.push_back(_rootNode);
    //std::cout << "rootNode: robotsPosition[0] = " << nodeRegistry.back().getPosition0() << std::endl;
    l.push_front(&nodeRegistry.back());
    victory = false;

/*    int dir = 0;
    std::cout << "isPossible(" << dir << "): " << l.back()->isPossible(dir) 
        << std::endl;*/
    
}


bool Handler::expansion0(Node* _node){
    //Node * currentNode = _node;
    if (_node->goalReached()){
        victory = true;
        std::cout << "GOAL REACHED!" << std::endl;
    
        std::cout << "victory depth:    " << _node->getDepth() << std::endl;
        std::cout << "l.size():     " << l.size() << std::endl;

        std::cout << "root nodes father: " << nodeRegistry.front().getFather() << std::endl;
        printWay(_node);
        return victory;
    }

    if (_node->getDepth() > 2){
            if (_node->equivState0(_node->getFather()->getFather())) {
                std::cout << "FUCKING WORKING EQUIVSTATE0. GRAND FATHER DETECTED!!!" << std::endl;
                l.pop_front();
                return false;   
            }
        }

    for(int direction = 0; direction < 4; direction++){
        l.front()->showValues();
        std::cout << "is possible (" << direction << "): " << l.front()->isPossible(direction) 
        << std::endl;

        if (l.front()->isPossible(direction)){
            nodeRegistry.push_back((_node->partialExpansion(direction)));
            l.push_back(&(nodeRegistry.back()));

            std::cout << std::endl << "FOR CYCLE EXPANSION0()" << std::endl;
            std::cout << std::endl << std::endl;
        } else {
            std::cout << std::endl << "NOT GOING IN DIRECTION: " << direction << std::endl;
        }
        std::cout << "********************" << std::endl;
    }
    std::cout << "depth after for:    " << l.front()->getDepth() + 1 << std::endl;
    
    std::cout << "********************" << std::endl;
    std::cout << "******END FOR*******" << std::endl;
    std::cout << "********************" << std::endl;

    l.pop_front();
    std::cout << "l.size():     " << l.size() << std::endl;

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

    if (nodeRegistry.front().goalReached()){
        victory = true;
        std::cout << "GOAL REACHED!" << std::endl;
        return;
    }else victory = false;

    while(!victory && (numberOfExpansions != 1))
    {
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
    while (current_point->getDepth() != 1){
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




