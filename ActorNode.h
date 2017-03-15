/*
 * ActorNode.h
 * Author: Ruoxin Huang, Muyang Wu
 * Date:  3/2/2017
 *
 * ActorNode.h is header file of ActorNode class.
 */
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
  bool done;
  string name;
  string movie;
  int distance;
  int year;
  ActorNode* prev;
  vector<Movies*> movies;
  vector<string> people;
  ActorNode(string n);
  void addMovie(Movies* m);
  /** Less-than comparison, so HCNodes will work in std::priority_queue
   *  We want small counts to have high priority.
   *  And we want to break ties deterministically.
   */
  bool operator<(const ActorNode& other);
};

class ActorNodePtrComp {
 public:
  bool operator()(ActorNode*& lhs, ActorNode*& rhs) const {
    return *lhs < *rhs;
  }
};
#endif // ACTORNODE_H
