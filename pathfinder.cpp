#include "ActorNode.h"
#include "ActorGraph.h"
#include "Movies.h"
#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#define MAX 2147483647

/*param: two actor names
  return: shortest path
*/
void BFS(ActorNode* actor1) {
  ActorNode* curr;
  ActorNode* currA;
  Movies* currM;
  queue<ActorNode*> queue;
  queue.push(actor1); //push origin actor into queue
  actor1.distance=0; //set distance to 0
  while(!queue.empty()){
    curr = queue.pop(); //pop element
    //for all movies the actor took part
    for(int i=0; i<curr->movies.size(); i++){
      currM = curr->movies[i];// set pointer to one of his movies
      //for all actors in the movie
      for(int j=0; j<currM->actors.size(); j++){
	currA = currM->actor[j]; //set pointer to one of its actor
	if(currA->distance==MAX){ //if actor is not already searched
	  currA->distance = curr->distance+1; //set distance to previous distance +1
	  currA->prev = curr;// set prev
	  currA->movie = currM->name;
	  queue->push(currA);//push it to queue
	}
      }
    }
  }
}

int main(int argc, char*argv[]) {
  /*if(argc != 5){
    cout << "invalid # of arguments" << endl;
    return -1;
  }*/
  ifstream infile1;
  infile1.open(argv[1], ios::in);
  //ifstream infile2(argv[3]);
  ActorGraph graph;
  graph.loadFromFile(argv[1], false);
  for(auto x:graph.actors){
    cout << x.first << endl;
  }
  
  vector<ActorNode*> vecA;
  //after BFS
  ActorNode* actor2;
  for(int i=0; i<actor2->distance; i++){
    vecA.insert(vecA.begin(),actor2);
    actor2 = actor2->prev;
  }
  cout<< vecA[0]->name << ;
  for(in i=1; i<vecA.size(); i++){
    cout <<"--"<<vecA[i]->movie<<"-->"<<vecA[i]->name<<;
  }
  return 0;

}
