#include "Handler.h"

#include <iostream>


//constructor
Handler::Handler(Node * _rootNode): rootNode(_rootNode){
    l.push_front(rootNode);
    victory = false;
}


bool Handler::expansion0(Node * _node){
    
    if (_node->goalReached()){
        victory = true;
        std::cout << "GOAL REACHED!" << std::endl;
        return victory;
    }

    for(int direction = 0; direction < 4; direction++){
        if (_node->isPossible(direction)){
            Node copy = _node->partialExpansion(direction);
            l.push_back(&copy);

            std::cout << std::endl << "FOR CYCLE EXPANSION0()" << std::endl;
            copy.showValues();
            std::cout << std::endl << std::endl;
        }
        std::cout << "********************" << std::endl;
    }
    
    l.remove(_node);
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
    //std::list <Node *> l;
    //l.push_front(rootNode);
    victory = false;
    int numberOfExpansions = 0;
    /*while(!victory || (numberOfExpansions == 3)){
        expansion0(l.front());
        numberOfExpansions++;
        std::cout << numberOfExpansions << std::endl;
    }*/
    l.front()->showValues();
    std::cout << "********************" << std::endl;
    expansion0(l.front());
    l.front()->showValues();
    std::cout << "********************" << std::endl;
    expansion0(l.front());
    l.front()->showValues();
    std::cout << "********************" << std::endl;
    std::cout << l.size() << std::endl;
}











