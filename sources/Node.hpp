/*
AUTHOR: BAR GOLDENBERG
*/
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

namespace ariel{
        class Node{
        public:
            Node();
            size_t id;
            vector<Node*> sons;
            size_t level;
            size_t size;
            string data;
            bool addSon(Node* n);
            bool removeSon(Node* n);
    };
}