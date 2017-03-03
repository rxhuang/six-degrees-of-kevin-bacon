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
  vector<Movies*> movies;
  string name;
  int 
  ActorNode(string n);
  void addMovie(Movies* m);

};

#endif
