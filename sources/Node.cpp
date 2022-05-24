/*
AUTHOR: BAR GOLDENBERG
*/
#include "Node.hpp"
#include<string>
#include<queue>
#include<iostream>
using namespace std;
using namespace ariel;

/**
 * @brief Construct a new Node:: Node object
 * 
 */
Node::Node(){
    // this->sons=new vector<Node*>();
    this->level=0;
    this->data = "";
    this->size=0;
    this->id=0;
    this->level=0;
}

/**
 * @brief adds a node to sons vector.
 * 
 * @param son 
 * @return true 
 * @return false 
 */
bool Node::addSon(Node* son){
    try {   
            son->level=this->level+1;
            son->id=this->size+1;
            this->size++;
            this->sons.push_back(son);
            return true;
        }catch(exception e){
            return false;
        }
}

/**
 * @brief removes a son from sons vector.
 * 
 * @param son 
 * @return true 
 * @return false 
 */
bool Node::removeSon(Node* son){
    for(auto i=this->sons.begin();i!=this->sons.end();i++){
        if(*i==son){
            this->sons.erase(i);
            return true;
        }
    }
    return false;
}