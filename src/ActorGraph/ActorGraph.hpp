/**
 * TODO: add file header
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP
#include <iostream>
#include <unordered_map>
#include <vector>
#include "ActorNode.hpp"
// #include "MovieNode.hpp"

using namespace std;

/**
 * TODO: add class header
 */

class ActorGraph {
  protected:
    // TODO: add data structures used in actor graph
    // ActorNode* actor;
    // MovieNode* movie;
    // unordered_map<string, ActorNode*> ActorMap;
    // unordered_map<pair<string, int>, MovieNode*> MovieMap;

    // unordered_map<string, ActorNode*> ActorMap;  // store Actors in a map
    // unordered_map<string, MovieNode*> MovieMap;

  public:
    unordered_map<string, ActorNode*> ActorMap;  // store Actors in a map
    unordered_map<string, MovieNode*> MovieMap;
    void build(string actor, string title, int year, string title_year);
    /* TODO */
    ActorGraph();

    /* TODO
     * 这个会在pathfinder.cpp里面被call, so the pathfinder.cpp can output the
     * shortest unweighted path between two given actors.
     * This function 已经完成了一部分了, is to load data(line by line) from the
     * input file. We should complete this function to build the entire graph
     * correctly.
     */
    bool buildGraphFromFile(const char* filename);

    /* TODO
     * 这个会在pathfinder.cpp里面被call
     */
    void BFS(const string& fromActor, const string& toActor,
             string& shortestPath);

    /* TODO
     * 这个会在linkpresictor.cpp里面被call, so the linkpredictor.cpp can output
     * the predicted new link between two actors in the future.
     */
    void predictLink(const string& queryActor, vector<string>& predictionNames,
                     unsigned int numPrediction);

    /* TODO
     *
     */
    ~ActorGraph();
};

#endif  // ACTORGRAPH_HPP
