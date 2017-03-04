#include "Movies.h"

using namespace std;

Movies::Movies(string n, int y){
  name = n;
  year = y;
}

void Movies::addActor(ActorNode* a){
  starring.push_back(a);
}
