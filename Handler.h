/*
Archive: node.h
Author: Diego Fabián Ledesma Motta
code: 1928161
email: diego.ledesma@correounivalle.edu.co
*/

#ifndef HANDLER_HH
#define HANDLER_HH

#include <iterator>
#include <list>

#include "Node.h"

class Handler{
    private:
        Node rootNode;
        std::list <Node *> l;
        bool victory;
        
        std::list <Node> nodeRegistry;


    public:
        Handler(Node rootNode);
        bool expansion0(Node* expNode); //best for breadthFirstSearch.
        void search(int mode);
        void breadthFirstSearch();
        void uniformCostSearch();
        void depthFirstSearch();
        void greedySearch(); //best-first search
        void aAsteriscSearch();
        Node* getFront();
};

#else
class Handler;
#endif