/*
 * ActorGraph.h
 * Author: Ruoxin Huang, Muyang Wu
 * Date:  3/2/2017
 *
 * This is the header file of ActorGraph class.
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H
#include "ActorNode.h"
#include "Movies.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include <queue>
#include "UnionFind.hpp"


// Maybe include some data structures here

using namespace std;

class ActorGraph {
public:
    ActorGraph(void);


    /*
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
     bool loadFromFile(const char* in_filename, bool use_weighted_edges);
     bool getOldestYear(const char* in_filename);
     void buildGraphByYear(const char* in_filename, int year);
     void buildExtensionGraph(const char* in_filename);
     void clear();
     void BFS(ActorNode*);
     void Dijk(ActorNode*);
     int curr_movie_year;
     unordered_map<string, ActorNode*> actors;
     unordered_map<string, Movies*> movies;

};


#endif // ACTORGRAPH_H
