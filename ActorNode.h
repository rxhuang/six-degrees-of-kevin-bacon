#ifndef ACTORNODE_H
#define ACTORNODE_H
#include "Movies.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Movies;
class ActorNode{
 public:
  string name;
  string moive;
  int distance;
  ActorNode* prev;
  vector<Movies*> movies;

  ActorNode(string n);
  void addMovie(Movies* m);
};

#endif
