#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP
#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

class UnionFind{
public:

  unordered_map<string, pair<string, int>> actorSet;

  UnionFind(){}
  ~UnionFind(){}

  string find(string name){
    if(actorSet[name].first !=name)
      actorSet[name].first = find(actorSet[name].first);
    else
      return actorSet[name].first;
}

  void unionJoin(string name1, string name2){
    string n1 = find(n1);
    string n2 = find(n2);

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

};
#endif
