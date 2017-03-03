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
/*ActorNode* BFS(ActorNode* actor1, ActorNode* actor2) {
  ActorNode* curr;
  ActorNode* currA;
  Movies* currM;
  queue<ActorNode*> queue;
  queue.push(actor1);
  actor1.distance=0;
  while(!queue.empty()){
    curr = queue.pop();
    for(int i=0; i<curr.movies.size(); i++){
      currM = curr.movies[i];
      for(int j=0; j<currM.actors.size(); j++){
	currA = currM.actor[j];
	if(currA.distance==MAX){
	  currA.distance = curr.distance+1;
	  currA.prev = curr;
	  queue.push(currA);
	}

      }
    }
  }

}*/

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
  return 0;

}
