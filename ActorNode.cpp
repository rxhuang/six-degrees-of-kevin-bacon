#include "ActorNode.h"
#define MAX 2147483647
using namespace std;

ActorNode::ActorNode(string n){
  name = n;
  distance = MAX;
  prev = NULL;
}

void ActorNode::addMovie(Movies* m){
  movies.push_back(m);
}

bool ActorNode::operator<(ActorNode const &other){
  return this->year>=other.year;
}
