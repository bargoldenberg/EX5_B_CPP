/*
AUTHOR: BAR GOLDENBERG
*/
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Node.hpp"
#include <map>
using namespace std;
namespace ariel{
    class OrgChart{
        private:  
            vector<Node*> rvrs_lvl_order;
            vector<Node*> pre_order_vec;
            vector<string> string_rlvl_order;
            vector<string> string_porder;
            vector<Node*> lvl_order;
            vector<string> string_lvl_order;
            void bfs();
            void revbfs();
            void pre_order(Node* root); 
            size_t height;
            size_t MC;
            Node* root;
            size_t chart_size;
        public:
            OrgChart();
            OrgChart(const OrgChart& o);
            OrgChart(const OrgChart&& o) noexcept;
            ~OrgChart();
            OrgChart& add_root(const string& root);
            OrgChart& add_sub(const string& exists,const string& new_node);
            void clear_all();
            std::vector<string>::iterator begin();
            std::vector<string>::iterator end();
            std::vector<string>::iterator begin_level_order();
            std::vector<string>::iterator end_level_order();
            std::vector<string>::iterator begin_reverse_order();
            std::vector<string>::iterator reverse_order();
            std::vector<string>::iterator begin_preorder();
            std::vector<string>::iterator end_preorder();
            OrgChart& operator=(const OrgChart& o);
            OrgChart& operator=(OrgChart&& o) noexcept;
            friend ostream& operator<<(ostream& output,OrgChart &chart);
            friend ostream& operator<<(ostream& output, const Node* n);
            friend ostream& operator<<(ostream& output, std::vector<Node*>::iterator it);
    };
}