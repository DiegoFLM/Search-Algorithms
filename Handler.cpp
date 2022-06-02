#include "Handler.h"

#include <iostream>


//constructor
Handler::Handler(Node _rootNode): rootNode(_rootNode){
    std::list <Node> nodeRegistry;
    //Node rooooot = _rootNode;
    //rootNode = _rootNode;
    Node nod555 = _rootNode;
    nodeRegistry.push_back(_rootNode);
    //nodeRegistry.back().setTPosition();
    std::cout << "rootNode: robotsPosition[0] = " << nodeRegistry.back().getPosition0() << std::endl;
    l.push_front(&nodeRegistry.back());
    victory = false;
    
    nodeRegistry.back().setAutoRef(&(nodeRegistry.back()));


    //nodeRegistry.back().getAutoRef()->showValues();
    //nodeRegistry.back().equivState0(nodeRegistry.back().getAutoRef());
    //nodeRegistry.back().getAutoRef()->equivState0(nodeRegistry.back().getAutoRef());
}


bool Handler::expansion0(Node* _node){
    
    if (_node->goalReached()){
        victory = true;
        std::cout << "GOAL REACHED!" << std::endl;
        return victory;
    }
    
    if (_node->equivState0(_node->getAutoRef())) {
        std::cout << "FUCKING WORKING EQUIVSTATE0!!!" << std::endl;
        //continue;   tPosition
        }

    for(int direction = 0; direction < 4; direction++){
        std::cout << _node->isPossible(direction) << std::endl;

        //Node iAmYourFather = *(_node.getFather());
        //if (_node.getFather()->equivState0(_node)) continue;
        /*if (_node.equivState0(*(_node.getAutoRef()))) {
            std::cout << "FUCKING WORKING EQUIVSTATE0!!!" << std::endl;
            continue;   
        }*/

        if (_node->isPossible(direction)){
            //Node copy = _node->partialExpansion(direction);
            nodeRegistry.push_back((_node->partialExpansion(direction)));
            l.push_back(&(nodeRegistry.back()));
            nodeRegistry.back().setAutoRef(&(nodeRegistry.back()));
            std::cout << std::endl << "FOR CYCLE EXPANSION0()" << std::endl;
            //copy.showValues();
            std::cout << std::endl << std::endl;
        }
        std::cout << "********************" << std::endl;
    }
    _node->equivState0(_node->getAutoRef());
    
//    l.remove(_node);
    l.pop_front();
    std::cout << l.size() << std::endl;

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
/*
    while(!victory //&& (numberOfExpansions != 3)
    ){
        expansion0(l.front());
        numberOfExpansions++;
        std::cout << numberOfExpansions << std::endl;
    }*/
    
    l.front()->showValues();
    std::cout << "********************" << std::endl;
    expansion0(l.front());
    l.front()->showValues();
    /*
    std::cout << "********************" << std::endl;
    expansion0(l.front());
    l.front().showValues();
    std::cout << "********************" << std::endl;
    expansion0(l.front());
    
    l.front().showValues();*/
    std::cout << "********************" << std::endl;
    std::cout << l.size() << std::endl;
}




Node* Handler::getFront(){
    return &(nodeRegistry.front());
}






