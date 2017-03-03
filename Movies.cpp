#include "Movies.h"

using namespace std;

Movies::Movies(string n, int year){
  name = n;
  year = year;
}

void Movies::addActor(ActorNode* a){
  starring.push_back(a);
}
