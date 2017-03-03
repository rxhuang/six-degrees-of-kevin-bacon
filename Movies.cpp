#include "Movies.h"

using namespace std;

Movies::Movies(string n){
  name = n;
}

void Movies::addActor(ActorNode* a){
  starring.push_back(a);
}
