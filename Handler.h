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
#include <chrono>
#include <vector>


#include "Node.h"

class Handler{
    private:
        Node rootNode;
        std::list <Node *> l;
        bool victory;
        
        std::list <Node> nodeRegistry;

        int minCost;

        std::vector <Node*> solutionPath;
        int victorysize;
        std::chrono::microseconds solutionTime;

        int numberOfExpansions;


    public:
        Handler(Node rootNode);
        Handler(Node fn, int _initialRobotPosition[2], int _shipsFuel[2], bool _foundItems[2],
                    bool _drivingShip[2]);
        bool expansion0(Node* expNode); //best for breadthFirstSearch.
        bool expansion1(Node* expNode); //best for uniformCostSearch.
        bool expansion2(Node* expNode);  //best for depthFirstSearch & greedySearch.
        bool expansion3(Node* _expNode); //best for A*
        void search(int mode);
        void breadthFirstSearch();
        void uniformCostSearch();
        void depthFirstSearch();
        void greedySearch(); //best-first search
        void aAsteriscSearch();
        Node* getFront();
        void printWay(Node* _node);
        void makeWay(Node* _vicNode);
        void showValsL(std::list<Node *> lst);
        void showValsNodeRegistry(std::list<Node> lst);

        Node* getVicWayNode(int position);
        int getVictorySize();
        int getSolutionTime();

        int getRobotsPosition0(int posNode);
        int getRobotsPosition1(int posNode);

        int getNumberOfExpansions();
};

#else
class Handler;
#endif