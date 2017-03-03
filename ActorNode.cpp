#include "ActorNode.h"
using namespace std;

ActorNode::ActorNode(string n){
  name = n;
}

void ActorNode::addMovie(Movies* m){
  movies.push_back(m);
}
