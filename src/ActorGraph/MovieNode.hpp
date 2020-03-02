/**
 * TODO: file header
 *
 * Author:Xuan Ding, xding@ucsd.edu
 *        Qilong Li, qil009@ucsd.edu
 *
 */
#ifndef MOVIENODE_HPP
#define MOVIENODE_HPP
#include <iostream>
#include <unordered_map>
#include <vector>
#include "ActorNode.hpp"
using namespace std;
class ActorNode;
class MovieNode {
  private:
  public:
    vector<ActorNode*> actor_vector;
    // unordered_map<string, ActorNode*> MovietoActor;
    string MovieName;
    int year;
    bool visited;
    ActorNode* prev;
    int dist;
    string MovieYear = "--[" + MovieName + "#@" + to_string(year) + "]-->";
    MovieNode(string title, int year)
        : MovieName(title), year(year), visited(false) {}

    void addActor(ActorNode* actor1) { actor_vector.push_back(actor1); }
};

#endif