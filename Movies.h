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
  int year;
  vector<ActorNode*> starring;
  Movies(string n, int y);
  void addActor(ActorNode* a);
};

#endif
