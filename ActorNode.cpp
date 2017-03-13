/*
 * ActorNode.cpp
 * Author: Ruoxin Huang, Muyang Wu
 * Date:  3/2/2017
 *
 * ActorNode.cpp is implementation file of ActorNode class.
 */
#include "ActorNode.h"
#define MAX 2147483647
using namespace std;
/*
 * Constructor of ActorNode class
 *
 * n - string variable to set the name of actor
 *
 * no return
 */
ActorNode::ActorNode(string n){
  name = n;
  distance = MAX;
  prev = NULL;
  year = 0;
  done = false;
}
/*
 * Add Movies Node into the vector of movies
 *
 * m - Movies node
 *
 * no return
 */
void ActorNode::addMovie(Movies* m){
  movies.push_back(m);
}
/*
 * Compare operator overloaded
 *
 * other - const reference of an ActorNode object
 *
 * return true if left arguments is smaller or equal to right arguments.
 */
bool ActorNode::operator<(ActorNode const &other){
  return this->distance>=other.distance;
}
