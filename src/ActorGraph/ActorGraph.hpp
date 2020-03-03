/**
 * TODO: add file header
 * Author:Xuan Ding, xding@ucsd.edu
 *        Qilong Li, qil009@ucsd.edu
 * This file includes class ActorGraph with have the functionality to build
 * actor class and movie class together to build a undirected and weighted
 * graph. this class contains unordered_maps as data structure as collections of
 * all moviesNodes and ActorNodes object pointers. this class provides function
 * to build graph and can build graph from external files. it also includes
 * Breath first search to output paths from one actor to another, as well as the
 * ability to predict links of one actor and predict their connections with
 * other actors.
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
    void Bfsreset();
    void build(const string& actor, const string& title, const int& year,
               const string& title_year);
    /* TODO
     *Initialize tow hashmaps to be empty initially.
     */
    ActorGraph();

    /* TODO
     * Build the actor graph from dataset file.
     * Each line of the dataset file must be formatted as:
     * ActorName <tab> MovieName <tab> Year
     * Two actors are connected by an undirected edge if they have worked in a
     * movie before. Here, call helper function build() to build the graph
     */
    bool buildGraphFromFile(const char* filename);

    /* TODO
     *This function performs breath first search to the graph. This function
     takes three strings as parameter, string fromActor is the actor name of the
     graph starting from, string toActor is is the destination of the graph. The
     paths from starting node to destination node will be written into the
     string shortestPath.
     */
    void BFS(const string& fromActor, const string& toActor,
             string& shortestPath);

    /* TODO
     * will be called in linkpresictor.cpp, so the linkpredictor.cpp can output
     * the predicted new link between two actors in the future.
     */
    void predictLink(const string& queryActor, vector<string>& predictionNames,
                     unsigned int numPrediction);

    /* TODO
     * Delete all actor nodes and movie nodes in two hashmaps
     */
    ~ActorGraph();
};

#endif  // ACTORGRAPH_HPP
