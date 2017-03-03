#ifndef MOVIES_H
#define MOVIES_H
#include "ActorNode.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class ActorNode;
class Movies{    
 public:
  string name;
  vector<ActorNode*> starring;
  Movies(string n);
  void addActor(ActorNode* a);
};

#endif
