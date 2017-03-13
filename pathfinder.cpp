/*
 * Pathfinder.cpp
 * Author: Ruoxin Huang, Muyang Wu
 * Date:  3/2/2017
 *
 * Pathfinder.cpp is meant to shortest path from one actors to another, via
 * BFS or Dijkstra's algorithm. Besides that, the pathfinder will calculate
 * how much time does it take to complete the algorithm.
 */
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
#include <cstdio>
#include <ctime>

/*
 * Load the graph from a tab-delimited file of actor->movie relationships. Then
 * load them into a vector of pairs
 *
 * in_filename - input filename
 * input - a vector of pairs that saves all actor pairs.
 *
 * no return
 */
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
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
    }
    infile.close();
}
//main func
int main(int argc, char*argv[]) {
  // check if enough arguments
  if(argc != 5){
    cout << "invalid # of arguments" << endl;
    return -1;
  }
  // initialize the "timer"
  clock_t start;
  double duration;
  start = clock();
  // initialize vector of pairs, input and output filestream, and ActorGraph
  // object
  string name;
  vector<pair<string, string>> actorsPair;
  bool weighted;
  ifstream infile1;
  infile1.open(argv[1], ios::in);
  ifstream infile2;
  infile2.open(argv[3], ios::in);
  ActorGraph graph;
  ofstream outfile;
  // check if weighted or not
  if(strcmp(argv[2], "u")){
    weighted = true;
    name = "Dijkstra's algorithm";
  }
  else{
    weighted = false;
    name = "BFS";
  }
  // load .tsv into graph
  graph.loadFromFile(argv[1], weighted);
  loadpair(argv[3], actorsPair);
  ActorNode * actor1;
  outfile.open(argv[4], ios::binary);
  //write the header
  outfile << "(actor)--[movie#@year]-->(actor)--..." << endl;
  //for each actor pairs in the vector, find respective nodes in the map and
  // do BFS or Dijkstra to find the path.
  for(int i = 0; i < actorsPair.size(); i++){
    graph.clear();
    vector<ActorNode*> vecA;
    actor1 = graph.actors.at(actorsPair[i].first);
    if(!weighted)
      graph.BFS(actor1);
    else
      graph.Dijk(actor1);
    ActorNode* actor2;
    actor2 = graph.actors.at(actorsPair[i].second);
    while(actor2->prev){
      vecA.insert(vecA.begin(),actor2);
      actor2 = actor2->prev;
    }
    vecA.insert(vecA.begin(),actor1);
    outfile<< "("<< vecA[0]->name << ")";
    for(int i=1; i<vecA.size(); i++){
        outfile <<"--"<< "["<<vecA[i]->movie << "#@" << vecA[i]->year<< "]" <<"-->" << "("<<vecA[i]->name << ")";
    }
    graph.clear();
    outfile << endl;
  }
  // close all files for reading or writing
  infile1.close();
  infile2.close();
  outfile.close();
  // print out the duration it takes to run this program
  duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
  cout<<"The " << name << " takes "<< duration << " seconds" <<'\n';
  return 0;

}
