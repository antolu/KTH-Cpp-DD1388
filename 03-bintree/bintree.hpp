#ifndef BINTREE_HPP
#define BINTREE_HPP

#include <iostream>
#include <string>

struct Node {
    int key;
    double data;
    Node * right;
    Node * left;
};

void insert(Node * & p, int key, double to_be_inserted);
void remove(Node * & p, const int & key);

Node * findNode(Node * p, const int & key);
Node * findMin(Node * p);
Node * findMax(Node * p);
const double & find(Node * p, const int & key);
double & edit(Node * p, const int & key);

void delete_tree(Node * & p);

unsigned int max_height(Node * p);
unsigned int min_height(Node * p);
unsigned int size(Node * p);
bool is_balanced(Node * p);

std::ostream& operator<<(std::ostream & ostream, Node * rhs);

#endif
