#include "ActorNode.h"
#include "ActorGraph.h"
#include "Movies.h"
#include <iostream>
#include <queue>
#include <string>
#define MAX 2147483647

/*param: two actor names
  return: shortest path
*/
ActorNode* BFS(ActorNode* actor1, ActorNode* actor2) {
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

}

int main() {
  ActorGraph graph;
  
}
