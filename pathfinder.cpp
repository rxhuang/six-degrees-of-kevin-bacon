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
	  currA->year = currM->year;
	  queue.push(currA);//push it to queue
	}
      }
    }
  }
}

void Dijk(ActorNode* actor1) {
  ActorNode* curr;
  ActorNode* currA;
  Movies* currM;
  priority_queue<ActorNode*, vector<ActorNode*>,ActorNodePtrComp> queue;
  int distance;
  queue.push(actor1); //push origin actor into queue
  actor1->distance=0; //set distance to 0
  while(!queue.empty()){
    curr = queue.top();
    queue.pop(); //pop element
    if(curr->done=false)
      curr->done=true;
    //for all movies the actor took part
    for(int i=0; i<curr->movies.size(); i++){
      currM = curr->movies[i];// set pointer to one of his movies
      //for all actors in the movie
      for(int j=0; j<currM->starring.size(); j++){
	currA = currM->starring[j]; //set pointer to one of its actor
	distance = curr->distance+1+(2015-currM->year);
	if(distance<currA->distance){ //if actor is not already searched
	  currA->distance = distance; //set distance to previous distance +1
	  currA->prev = curr;// set prev
	  currA->movie = currM->name;
	  currA->year = currM->year;
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
  ofstream outfile;
  if(strcmp(argv[2], "u"))
    weighted = true;
  else
    weighted = false;
  graph.loadFromFile(argv[1], weighted);
  loadpair(argv[3], actorsPair);
  ActorNode * actor1;
  outfile.open(argv[4], ios::binary);
  //write the header
  outfile << "(actor)--[movie#@year]-->(actor)--..." << endl;
  for(int i = 0; i < actorsPair.size(); i++){
    graph.clear();
    vector<ActorNode*> vecA;
    actor1 = graph.actors.at(actorsPair[i].first);
    if(!weighted)
      BFS(actor1);
    else
      Dijk(actor1);
    ActorNode* actor2;
    actor2 = graph.actors.at(actorsPair[i].second);
    while(actor2->prev){
      vecA.insert(vecA.begin(),actor2);
      actor2 = actor2->prev;
    }
    vecA.insert(vecA.begin(),actor1);
    outfile<< "("<< vecA[0]->name << ")";
    for(int i=1; i<vecA.size(); i++){
      /*outfile <<"--"<< "["<<vecA[i]->movie << "#@" << (graph.movies.at(vecA[i]->movie))->year<< "]" <<"-->" << "("<<vecA[i]->name << ")";*/
        outfile <<"--"<< "["<<vecA[i]->movie << "#@" << vecA[i]->year<< "]" <<"-->" << "("<<vecA[i]->name << ")";
    }
    graph.clear();
    outfile << endl;
  }
  infile1.close();
  infile2.close();
  outfile.close();
  return 0;

}
