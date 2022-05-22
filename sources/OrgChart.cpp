
#include "OrgChart.hpp"
#include<string>
#include<queue>
#include<iostream>
using namespace std;
using namespace ariel;




void OrgChart::clear_all(){
    this->pre_order_vec.clear();
    this->lvl_order.clear();
    this->rvrs_lvl_order.clear();
    this->string_porder.clear();
    this->string_lvl_order.clear();
    this->string_rlvl_order.clear();
}
/**
 * @brief Construct a new Org Chart:: Org Chart object
 * 
 */
OrgChart::OrgChart(){
    this->root=nullptr;
    this->chart_size=0;
    this->MC=0;
    this->height=0;
}

void del_preorder(Node* root){
    if(root==nullptr){
        return;
    }
    if(root->sons.empty()){
        return;
    }
    for(auto i = root->sons.begin();i!=root->sons.end();i++){
        del_preorder((*i));
    }
    delete root;
}
/**
 * @brief Destroy the Org Chart:: Org Chart object
 * 
 */
OrgChart::~OrgChart(){
    this->bfs();
    for(size_t i = 0;i<this->lvl_order.size();i++){
        delete this->lvl_order.at(i);
    }

}
/**
 * @brief Breath first search algorithm for level order traversal.
 * 
 */
void OrgChart::bfs(){
    if(this->root==nullptr){return;}
    this->clear_all();
    Node* s = this->root;
    queue<Node*> q;
    vector<bool> visited;
    visited.resize(this->chart_size,false);
    visited[s->id]=true;
    q.push(s);
    while(!q.empty()){
        s=q.front();
        this->lvl_order.push_back(s);
        q.pop();
        for(size_t i = 0;i<s->sons.size();i++){
            Node* n = s->sons.at(i);
            if(!visited[n->id]||visited[n->id]){
                visited[n->id]=true;
                q.push(n);
            }
        }
    }
    
}

/**
 * @brief Creates root for chart, if root exists replaces its contents.
 * 
 * @param root 
 * @return OrgChart& 
 */
OrgChart& OrgChart::add_root(const string& root){
    if(this->root == nullptr){
        Node* addroot = new Node();
        this->MC++;
        addroot->data=root;
        this->root=addroot;
        this->chart_size+=1;
        return *this;
    }
    this->root->data = root;
    return *this;
}
/**
 * @brief adds subordinant in organization.
 * 
 * @param exists 
 * @param new_node 
 * @return OrgChart& 
 */
OrgChart& OrgChart::add_sub(const string& exists,const string& new_node){
    if(this->root==nullptr){throw std::invalid_argument("cant add subordinant without root");}
    this->chart_size+=1;
    this->MC++;
    this->bfs();
    for(auto i = this->lvl_order.begin();i!=this->lvl_order.end();i++){
        if((*i)->data==exists){
            Node* tmp = new Node();
            tmp->data=new_node;
            (*i)->addSon(tmp);
            tmp->id = this->chart_size;
            if(tmp->level>this->height){
                this->height=tmp->level;
            }
            return *this;
        }
    }
    throw std::invalid_argument("no such employer");
    //return *this;
}
/**
 * @brief returns iterator for level order traversal (using bfs).
 * 
 * @return std::vector<string>::iterator 
 */
std::vector<string>::iterator OrgChart::begin_level_order(){
    this->clear_all();
    if(this->root==nullptr){throw invalid_argument("chart_is_empty");}
    this->bfs();
    this->string_lvl_order.clear();
    for(auto i = this->lvl_order.begin();i!=this->lvl_order.end();i++){
        this->string_lvl_order.push_back((*i)->data);
    }
    return this->string_lvl_order.begin();

}
/**
 * @brief returns iterator for level order traversal (using bfs).
 * 
 * @return std::vector<string>::iterator 
 */
std::vector<string>::iterator OrgChart::end_level_order(){
    if(this->root==nullptr){throw invalid_argument("chart_is_empty");}
    return this->string_lvl_order.end();
}

/**
 * @brief Helper method for reverse level order.
 * 
 * @param v 
 * @param start 
 * @param end 
 */
void reverse_part(vector<Node*>& v,size_t start,size_t end){
    while(start<end){
        Node* tmp = v[start];
        v[start]=v[end];
        v[end]=tmp;
        start++;
        end--;
    }
}
/**
 * @brief this method calls BFS reverses the vector returned from BFS, and then reverses each level respectfully.
 * For Example:
 * \__CEO
        |--CTO
        |   \__VP_SW
        |--CFO
        \__COO
            \__VP_BI
            BFS RETURNS -> {CEO,CTO,CFO,COO,VP_SW,VP_BI} -> REVERSE -> {VP_BI,VP_SW,COO,CFO,CTO,CEO}->
            CLASSIFY BY LEVEL -> {{VP_BI,VP_SW},{COO,CFO,CTO},{CEO}}->
            REVERSE BY LEVEL -> {{VP_SW,VP_BI},{CTO,CFO,COO},{CEO}}->
            {VP_SW,VP_BI,CTO,CFO,COO,CEO}-> VALID REVERSE LEVEL OREDER
 * 
 */
void OrgChart::revbfs(){
    this->bfs();
    for(size_t i=this->lvl_order.size()-1;i>0;--i){
        this->rvrs_lvl_order.push_back(this->lvl_order.at(i));
    }
    this->rvrs_lvl_order.push_back(this->lvl_order.at(0));
    size_t indx=0;
    size_t start=0;
    size_t end=0;
    for(size_t i=this->height;i>0;i--){
        start = indx;   
        while(indx<this->chart_size&&this->rvrs_lvl_order.at(indx)->level==i){
            indx++;
        }
        end = indx-1;
        reverse_part(this->rvrs_lvl_order,start,end);
    }
}

/**
 * @brief returns iterator for reverse level order traversal (using revbfs).
 * 
 * @return std::vector<string>::iterator 
 */
std::vector<string>::iterator OrgChart::begin_reverse_order(){
    if(this->root==nullptr){throw invalid_argument("chart_is_empty");}
    revbfs();
    this->string_rlvl_order.clear();
    for(auto i = this->rvrs_lvl_order.begin();i!=this->rvrs_lvl_order.end();i++){
        this->string_rlvl_order.push_back((*i)->data);
    }
    return this->string_rlvl_order.begin();
}

/**
 * @brief returns iterator for reverse level order traversal (using revbfs).
 * 
 * @return std::vector<string>::iterator 
 */
std::vector<string>::iterator OrgChart::reverse_order(){
    if(this->root==nullptr){throw invalid_argument("chart_is_empty");}
    return this->string_rlvl_order.end();
}

/**
 * @brief PreOrder Algorithm adapted from root left right to root all sons.
 * 
 * @param root 
 */
void OrgChart::pre_order(Node* root){
    if(this->root==nullptr){throw invalid_argument("chart_is_empty");}
    if(root==nullptr){
        return;
    }
    this->pre_order_vec.push_back(root);
    if(root->sons.empty()){
        return;
    }
    for(auto i = root->sons.begin();i!=root->sons.end();i++){
        pre_order((*i));
    }
}

/**
 * @brief returns iterator for pre order traversal.
 * 
 * @return std::vector<string>::iterator 
 */
std::vector<string>::iterator OrgChart::begin_preorder(){
    if(this->root==nullptr){throw invalid_argument("chart_is_empty");}
    this->clear_all();
    pre_order(this->root);
    for(auto i = this->pre_order_vec.begin();i!=this->pre_order_vec.end();i++){
        this->string_porder.push_back((*i)->data);
    }
    return this->string_porder.begin();
}

/**
 * @brief returns iterator for pre order traversal.
 * 
 * @return std::vector<string>::iterator 
 */
std::vector<string>::iterator OrgChart::end_preorder(){
    if(this->root==nullptr){throw invalid_argument("chart_is_empty");}
    return this->string_porder.end();
}

/**
 * @brief returns level order iterator.
 * 
 * @return vector<string>::iterator 
 */
vector<string>::iterator OrgChart::begin(){
    this->clear_all();
    if(this->root==nullptr){throw invalid_argument("chart_is_empty");}
    return this->begin_level_order();
}

/**
 * @brief returns level order iterator
 * 
 * @return vector<string>::iterator 
 */
vector<string>::iterator OrgChart::end(){
    if(this->root==nullptr){throw invalid_argument("chart_is_empty");}
    return this->end_level_order();
}

/**
 * @brief recursive function for printing orgchart
 * 
 * @param output 
 * @param n 
 * @param last 
 * @param laststring 
 * @return ostream& 
 */
ostream& printVertex(ostream& output, const Node* n, bool last, const string& laststring) {
    string end;
    string next;
    if(!last){
        end= "|--";
        next = "|   ";
    }else{
        end = "\\__";
        next = "   ";
    }
    string current = laststring + end + n->data;
    string nextString = laststring + next;
    output << current << endl;
    for (size_t i = 0; i < n->sons.size(); i++) {
        printVertex(output, n->sons.at(i), i == n->sons.size()-1, nextString);
    }
    return output;
}
/**
 * @brief output operator override.
 * 
 * @param output 
 * @param chart 
 * @return ostream& 
 */
ostream& ariel::operator<<(std::ostream &output, OrgChart &chart) {
    return printVertex(output, chart.root, true, "");
}






