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
            Node(const Node& n);
            Node(const Node&& n) noexcept;
            //~Node();
            size_t id;
            vector<Node*> sons;
            size_t level;
            size_t size;
            string data;
            Node& operator=(const Node& n);
            Node& operator=(Node&& n) noexcept;
            bool addSon(Node* n);
            bool removeSon(Node* n);
    };
}