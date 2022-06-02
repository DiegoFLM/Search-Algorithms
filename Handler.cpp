#include "Handler.h"

#include <iostream>


//constructor
Handler::Handler(Node _rootNode): rootNode(_rootNode){
    l.push_front(rootNode);
    victory = false;
    std::list <Node> nodeRegistry;
    nodeRegistry.push_back(_rootNode);
    _rootNode.setAutoRef(&(nodeRegistry.back()));
}


bool Handler::expansion0(Node _node){
    
    if (_node.goalReached()){
        victory = true;
        std::cout << "GOAL REACHED!" << std::endl;
        return victory;
    }
    
    if (_node.equivState0(*(_node.getAutoRef()))) {
            std::cout << "FUCKING WORKING EQUIVSTATE0!!!" << std::endl;
            //continue;   tPosition
        }

    for(int direction = 0; direction < 4; direction++){
        std::cout << _node.isPossible(direction) << std::endl;

        //Node iAmYourFather = *(_node.getFather());
        //if (_node.getFather()->equivState0(_node)) continue;
        /*if (_node.equivState0(*(_node.getAutoRef()))) {
            std::cout << "FUCKING WORKING EQUIVSTATE0!!!" << std::endl;
            continue;   
        }*/

        if (_node.isPossible(direction)){
            //Node copy = _node->partialExpansion(direction);
            l.push_back((_node.partialExpansion(direction)));

            std::cout << std::endl << "FOR CYCLE EXPANSION0()" << std::endl;
            //copy.showValues();
            std::cout << std::endl << std::endl;
        }
        std::cout << "********************" << std::endl;
    }
    _node.equivState0(*(_node.getAutoRef()));
    
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

    if (rootNode.goalReached()){
        victory = true;
        std::cout << "GOAL REACHED!" << std::endl;
        return;
    }
/*
    while(!victory //&& (numberOfExpansions != 3)
    ){
        expansion0(l.front());
        numberOfExpansions++;
        std::cout << numberOfExpansions << std::endl;
    }*/
    
    l.front().showValues();
    std::cout << "********************" << std::endl;
    expansion0(l.front());
    l.front().showValues();
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











