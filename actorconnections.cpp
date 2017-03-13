/*
 * Actorconnections.cpp
 * Author: Ruoxin Huang, Muyang Wu
 * Date:  3/2/2017
 *
 * Actorconnections.cpp is meant to give the year that after such will two Actors connected.
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
  // pretty much copy the whole thing from loadFromFile functions from ActorGraph.cpp
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
  if(argc != 4 && argc != 5){
    cout << "invalid # of arguments" << endl;
    return -1;
  }
  //Initialize graph and output stream
  string name;
  vector<pair<string, string>> actorsPair;
  vector<pair<string, string>> temp;
  ActorGraph graph;
  ofstream outfile;
  if(argc == 4)
    name = "uf";
  else if(strcmp(argv[5], "bfs"))
    name = "uf";
  else
    name = "bfs";
  //Initialize two input file streams
  ifstream infile1;
  infile1.open(argv[1], ios::in);
  ifstream infile2;
  infile2.open(argv[2], ios::in);
  //load graph once and find the oldest movie year
  graph.loadFromFile(argv[1]);
  loadpair(argv[2], actorsPair);
  temp = actorsPair;
  int size = temp.size();
  //initialize the movie year vector with size of actorsPair
  vector<int> movie_year(size, 0);
  //initialize two actor node for BFS
  ActorNode * actor1;
  ActorNode * actor2;
  // open the file for output
  outfile.open(argv[3], ios::binary);
  //set to beginning of the file
  infile1.clear();
  infile1.seekg(0, ios::beg);
  //for each movie, from the oldest year to 2015 buildgraph and then do BFS to find whether two actors are connected or not
  if(name == "bfs"){
  for(int i = graph.curr_movie_year; i < 2016; i++){
    //adding nodes to graphs via ActorGraph object
    graph.buildGraph(argv[1], i);
    for(int j = 0; j < size; j++){
      //chech if both actors are in the graph or not
      if(graph.actors.find(temp[j].first) != graph.actors.end() && graph.actors.find(temp[j].second) != graph.actors.end() ){
        // set both actor to respectively nodes
        actor1 = graph.actors.at(temp[j].first);
        actor2 = graph.actors.at(temp[j].second);
        //clear graph then BFS
        graph.clear();
        graph.BFS(actor1);
        // while actor has prev node go to prev, then compre if actor1 = actor2
        while(actor2->prev)
          actor2 = actor2->prev;
        if(actor2 == actor1){
          movie_year[j] = i;
          //set temp[j] to null so next time search wont replace year again
          temp[j] = make_pair(NULL, NULL);
        }
      }
    }
    //set to beginning of the files
    infile1.clear();
    infile1.seekg(0, ios::beg);
  }
}
else{
  for(int i = graph.curr_movie_year; i < 2016; i++){
    //adding nodes to graphs via ActorGraph object
    graph.buildUnionFind(argv[1], i);
    for(int j = 0; j < size; j++){
      //chech if both actors are in the graph or not
      if(graph.uf.find(temp[j].first) == graph.uf.find(temp[j].second)){
          movie_year[j] = i;
          //set temp[j] to null so next time search wont replace year again
          temp[j] = make_pair(NULL, NULL);
        }
      }
      //set to beginning of the files
      infile1.clear();
      infile1.seekg(0, ios::beg);

  }

}



  //write the header and additional informations
  outfile << "Actor1\tActor2\tYear" << endl;
  for(int i = 0; i < actorsPair.size(); i++){
    outfile << actorsPair[i].first << "\t" << actorsPair[i].second << "\t" << movie_year[i] << endl;
  }
  //close all files and end
  infile1.close();
  infile2.close();
  outfile.close();
  return 0;

}
