#ifndef UNIONFIND_H
#define UNIONFIND_H
#include <unordered_map>
#include <fstream>
#include <utility>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
using namespace std;

class UnionFind{
 public:

  unordered_map<string, pair<string, int>> actorSet;
  unordered_multimap<string, string> ufHash;
  UnionFind(){}
  ~UnionFind(){}

  /*
   * find the actors if not add them in, and then return itself
   *
   * string - name of the actors that needs to be found
   *
   * return a string if found otherwise itself
   */
  string find(string name){
    if(actorSet.find(name) == actorSet.end())
      actorSet.emplace(name, make_pair(name, 1));
    if(actorSet[name].first !=name)
      actorSet[name].first = find(actorSet[name].first);

    return actorSet[name].first;

  }
  /*
   * join to actor together
   *
   * string - name of the first actors to be joined
   * string - name of the second actors to be joined
   *
   * return nothing
   */
  void unionJoin(string name1, string name2){
    string n1 = find(name1);
    string n2 = find(name2);

    if(n1==n2)
      return;
    else if(actorSet[n1].second >= actorSet[n2].second){
      actorSet[n2].first = n1;
      actorSet[n1].second = actorSet[n1].second + actorSet[n2].second;
    }
    else{
      actorSet[n1].first = n2;
      actorSet[n2].second = actorSet[n1].second + actorSet[n2].second;
    }
  }
  /*
   * build the disjoint set
   *
   * in_filename - the file that needs to be parsed
   * year - at which year movies and actors that needs to be joined
   *
   * return nothing 
   */
  void buildUnionFind(const char* in_filename, int year){
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
        if(movie_year == year){
          ufHash.emplace(movie_title, actor_name);
        if(actorSet.find(actor_name) == actorSet.end())
          actorSet.emplace(actor_name, make_pair(actor_name, 1));
          auto range = ufHash.equal_range(movie_title);
          for(auto it = range.first; it != range.second; ++it ){
             if(it->second != actor_name)
   	         unionJoin(it->second, actor_name);
                     }

      }
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
    }
    infile.close();

  }



};
#endif
