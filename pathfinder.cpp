#include "ActorNode.h"
#include "ActorGraph.h"
#include "Movies.h"
#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <utility>
#include <sstream>
#define MAX 2147483647
#include <string.h>

/*param: two actor names
  return: shortest path
*/
void BFS(ActorNode* actor1) {
  ActorNode* curr;
  ActorNode* currA;
  Movies* currM;
  queue<ActorNode*> queue;
  queue.push(actor1); //push origin actor into queue
  actor1->distance=0; //set distance to 0
  while(!queue.empty()){
    curr = queue.front();
    queue.pop(); //pop element
    //for all movies the actor took part
    for(int i=0; i<curr->movies.size(); i++){
      currM = curr->movies[i];// set pointer to one of his movies
      //for all actors in the movie
      for(int j=0; j<currM->starring.size(); j++){
	currA = currM->starring[j]; //set pointer to one of its actor
	if(currA->distance==MAX){ //if actor is not already searched
	  currA->distance = curr->distance+1; //set distance to previous distance +1
	  currA->prev = curr;// set prev
	  currA->movie = currM->name;
	  queue.push(currA);//push it to queue
	}
      }
    }
  }
}
void loadpair(const char* in_filename, vector<pair<string, string>> &input){
  // Initialize the file stream
  ifstream infile(in_filename);

  bool have_header = false;

  // keep reading lines until the end of file is reached
  while (infile) {
      string s;

      // get the next line
      if (!getline( infile, s )) break;

      if (!have_header) {
          // skip the header
          have_header = true;
          continue;
      }

      istringstream ss( s );
      vector <string> record;

      while (ss) {
          string next;

          // get the next string before hitting a tab character and put it in 'next'
          if (!getline( ss, next, '\t' )) break;

          record.push_back( next );
      }

      if (record.size() != 2) {
          // we should have exactly 3 columns
          continue;
      }

      string actor1(record[0]);
      string actor2(record[1]);
      input.insert(input.end(), make_pair(actor1, actor2));
    }
}
int main(int argc, char*argv[]) {
  /*if(argc != 5){
    cout << "invalid # of arguments" << endl;
    return -1;
  }*/
  vector<pair<string, string>> actorsPair;
  bool weighted;
  ifstream infile1;
  infile1.open(argv[1], ios::in);
  ifstream infile2;
  infile2.open(argv[3], ios::in);
  ActorGraph graph;
  if(strcmp(argv[2], "u"))
    weighted = false;
  else
    weighted = true;
  graph.loadFromFile(argv[1], weighted);
  loadpair(argv[3], actorsPair);
  vector<ActorNode*> vecA;
  ActorNode * actor1;
  for(int i = 0; i < actorsPair.size(); i++){
    actor1 = graph.actors.at(actorsPair[i].first);
    BFS(actor1);
    ActorNode* actor2;
    actor2 = graph.actors.at(actorsPair[i].second);
    for(int i=0; i<actor2->distance; i++){
      vecA.insert(vecA.begin(),actor2);
      actor2 = actor2->prev;
    }
    cout<< vecA[0]->name << endl;
    for(int i=1; i<vecA.size(); i++){
      cout <<"--"<<vecA[i]->movie<<"-->"<<vecA[i]->name<< endl;
    }
  }
  return 0;

}
