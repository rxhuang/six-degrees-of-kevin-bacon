/*
 * ActorGraph.cpp
 * Author: Ruoxin Huang, Muyang Wu
 * Date:  3/2/2017
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorGraph.h"

using namespace std;

ActorGraph::ActorGraph(void) {}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
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

        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);
        // insert actors and movies into respective map
        if(actors.find(actor_name) == actors.end() && movies.find(movie_title) == movies.end()){
          // no actor or movie exists, add new actor and movie
          ActorNode* a = new ActorNode(actor_name);
          Movies* m = new Movies(movie_title,movie_year);
          a->addMovie(m);
          actors.emplace(actor_name, a);
          m->addActor(a);
          movies.emplace(movie_title, m);
        }
        else if(actors.find(actor_name) != actors.end() && movies.find(movie_title) != movies.end()){

          //both actor and movie exists, add respective pointers to them
          (actors.find(actor_name))->second->addMovie((movies.find(movie_title))->second);
          (movies.find(movie_title))->second->addActor((actors.find(actor_name))->second);

        }
        else if(actors.find(actor_name) != actors.end() && movies.find(movie_title) == movies.end()){
          //actors exists, create new movie and add actor's pointer
          Movies * m = new Movies(movie_title,movie_year);

          m->addActor((actors.find(actor_name))->second);

          movies.emplace(movie_title, m);

          //add new movie pointer to actor
          (actors.find(actor_name))->second->addMovie(m);


        }
        else if(actors.find(actor_name) == actors.end() && movies.find(movie_title) != movies.end()){
          // actor does not exist, create new actor and add respective movie pointer to it

          ActorNode * a = new ActorNode(actor_name);
          a->addMovie((movies.find(movie_title))->second);
          actors.emplace(actor_name, a);
          // add new actor pointer to movies
          (movies.find(movie_title))->second->addActor(a);

        }
        // we have an actor/movie relationship, now what?
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}
