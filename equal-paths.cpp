#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include "equal-paths.h"
#include <utility> 
#include <algorithm> 
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
pair<int, bool> checkPaths(Node* node) {
  if(node == nullptr){
    return (make_pair(0, true));
  }
  pair<int, bool> left = checkPaths(node->left);
  pair<int, bool> right = checkPaths(node->right);

  if(!left.second || !right.second || left.first!=right.first){
    return (make_pair(0, false));
  }

  return std::make_pair(std::max(left.first, right.first) + 1, true);
}

bool equalPaths(Node * root)
{
    // Add your code below
  return checkPaths(root).second;
}

