/*
 * Movies.cpp
 * Author: Ruoxin Huang, Muyang Wu
 * Date:  3/2/2017
 *
 * Movies.cpp is implementation file of Movies class.
 */
#include "Movies.h"

using namespace std;
/*
 * Constructor of Movies class
 *
 * n - string variable to set the name of movies
 * y - set the year of the movie
 * no return
 */
Movies::Movies(string n, int y){
  name = n;
  year = y;
}
/*
 * Add one ActorNode into vector of actors node
 *
 * a - an ActorNode that needs to add into vector 
 *
 * no return
 */
void Movies::addActor(ActorNode* a){
  starring.push_back(a);
}
