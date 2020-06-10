#include "bintree.hpp"
#include <stdexcept>

void insert(Node * & p, int key, double data) {
  if (p == nullptr) {
    p = new Node();
    p->key = key;
    p->data = data;
  }
  else if (key > p->key)
    insert(p->right, key, data);
  else if (key < p->key) 
    insert(p->left, key, data);
  else 
    p->data = data;
}

void remove(Node * & p, const int & key) {
  if (p == nullptr) {
    throw std::out_of_range("Key out of range!");
  } else if (key < p->key)
    remove(p->left, key);
  else if (key > p->key)
    remove(p->right, key);
  else // p->key == key
  {
    Node * temp = nullptr;
    if (p->right && p->left) {
      /* find replacement */
      //Node * min = p->right;
      Node * min = findMin(p->right);
      p->key = min->key;
      p->data = min->data;
      remove(p->right, min->key);
    }
    else if (p->left) {
      temp = p;
      p = p->left;
    }
    else if (p->right) {
      temp = p;
      p = p->right;
    }
    else {
      temp = p;
      p = nullptr;
    }
    if (temp != nullptr)
      delete temp;
  }
}

Node * findNode(Node * p, const int & key) {
  if (p == nullptr)
    throw std::out_of_range("Key out of range!");
  else if (key > p->key)
    return findNode(p->right, key);
  else if (key < p->key)
    return findNode(p->left, key);
  else
    return p;
}

Node * findMin(Node * p) {
  if (p == nullptr)
    throw std::out_of_range("p is a nullpointer");
  while (p->left != nullptr)
    p = p->left;
  return p;
}

Node * findMax(Node * p) {
  if (p == nullptr)
    throw std::out_of_range("p is a nullpointer");
  while (p->right != nullptr)
    p = p->right;
  return p;
}
  
const double & find(Node * p, const int & key) {
  if (p == nullptr)
    throw std::out_of_range("p is a nullpointer");
  return findNode(p, key)->data;
}

double & edit(Node * p, const int & key) {
  if (p == nullptr)
    throw std::out_of_range("p is a nullpointer");
  return findNode(p, key)->data;
}

void delete_tree(Node * & p) {
  if (p == nullptr)
    return;
  
  delete_tree(p->left);
  delete_tree(p->right);
  delete p;
  p = nullptr;
}

unsigned int max_height(Node * p) {
  if (p == nullptr)
    return 0;
  return std::max(max_height(p->left), max_height(p->right)) + 1;
}

unsigned int min_height(Node * p) {
  if (p == nullptr)
    return 0;
  return std::min(min_height(p->left), min_height(p->right)) + 1;
}

unsigned int size(Node * p) {
  if (p == nullptr)
    return 0;

  /* size of this node tree is size of children + itself */
  return size(p->left) + size(p->right) + 1;
}

bool is_balanced(Node * p) {
  if (p == nullptr)
    return true;

  /* Is balanced if height diff is <= 1, and all subtrees are balanced */
  if (std::abs((int) max_height(p->left) - (int) max_height(p->right)) <= 1 && is_balanced(p->left) && is_balanced(p->right))
    return true;
  else
    return false;
}

std::ostream& operator<<(std::ostream & ostream, Node * rhs) {
  if (!rhs)
    return ostream;
  else    
    return ostream << "(" << rhs->left << " " << rhs->key << ":" << rhs->data << " " << rhs->right << ")";
}

