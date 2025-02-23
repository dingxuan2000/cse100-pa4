/**
 * TODO: file header
 *
 * Author:Xuan Ding, xding@ucsd.edu
 *        Qilong Li, qil009@ucsd.edu
 * this file implements the class ActorNode, which provides actor nodes that
 * acts as vertices of the actorGraph class
 *
 */
#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP

#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "MovieNode.hpp"
using namespace std;

/** A class, instances of which are nodes in movie.
 */

class MovieNode;
class ActorNode {
  public:
    vector<MovieNode*> movies_vector;
    string actorName;
    bool visited = false;
    MovieNode* prev;
    int dist;

    ActorNode(string name) : actorName(name) {}
    void addMovie(MovieNode* movie1) { movies_vector.push_back(movie1); }
};

#endif