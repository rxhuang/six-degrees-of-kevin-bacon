/*
 * Movies.h
 * Author: Ruoxin Huang, Muyang Wu
 * Date:  3/2/2017
 *
 * Movies.h is header file of Movies class.
 */
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
  vector<string> actorNames;
  Movies(string n, int y);
  void addActor(ActorNode* a);
};

#endif // MOVIES_H
