/**
 * TODO: file header
 *
 * Author:Xuan Ding, xding@ucsd.edu
 *        Qilong Li, qil009@ucsd.edu
 *
 */
#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP
#include <iostream>
#include <vector>
using namespace std;
#include "MovieNode.hpp"
class ActorNode {
  private:
  public:
    string actor_name;  // the name of the actor
    // a vector to store the movies that this actor has participanted
    vector<MovieNode*> movies;

    /* Constructor that initialize a ActorNode */
    ActorNode(string name) : actor_name(name) {}
};

#endif