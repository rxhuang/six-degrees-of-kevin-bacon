/*
 * extension.cpp
 * Author: Ruoxin Huang, Muyang Wu
 * Date:  3/2/2017
 *
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

int main(int argc, char*argv[]) {
  // check if enough arguments
  if(argc != 4){
    cout << "invalid # of arguments" << endl;
    return -1;
  }
  ifstream infile1;
  infile1.open(argv[1], ios::in);
  ActorGraph graph;

  string person1 = argv[2];
  string person2 = argv[3];

  // load .txt into graph
  graph.buildExtensionGraph(argv[1]);

  vector<string> dest;
    for (auto it = graph.actors[person1]->people.begin(); it != graph.actors[person1]->people.end(); ++it)
{
    if (graph.actors[person2]->people.find(*it) != graph.actors[person2]->people.end())
    {
        dest.push_back(*it);
    }

for (auto a = dest.begin(); a != dest.end(); ++a)
cout << "For user(ID:) " << person1 << " and " << person2 << ", those are the multual friends " << *a << endl;
  }
  if(dest.size() == 0)
  cout << "Unfortunately, they dont have any mutual friends" << endl;

  infile1.close();
  return 0;

}
