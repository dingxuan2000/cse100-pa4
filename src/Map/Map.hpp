/**
 * TODO: add file header
 * Author:Xuan Ding, xding@ucsd.edu
 *        Qilong Li, qil009@ucsd.edu
 * This file includes class map with have the functionality to build a
undirected and weighted graph. this class contains Edge and Vertex as data
structure. this class provides function to build graph and can build graph from
external files. it also includes three main functions: Dijkstra- a weighted
search of shortest path, findMST-returns a vector of edge of graph to create a
minimum spanning tree, cruicialroads()- to return vector containing bridges of
this graph.
 */

#ifndef MAP_HPP
#define MAP_HPP

#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "Edge.hpp"

using namespace std;
struct cmpVertex {
    bool operator()(pair<Vertex*, int>& w1, pair<Vertex*, int>& w2) const {
        // when two words' frequencies are different
        if (w1.second != w2.second) {
            return w1.second > w2.second;
        } else {
            return w1.first->weight < w2.first->weight;
        }
    }
};
struct cmpEdge {
    bool operator()(pair<Edge*, float>& e1, pair<Edge*, float>& e2) const {
        if (e1.second != e2.second) {
            return e1.second > e2.second;
        } else {
            return e1.first->weight < e2.first->weight;  //有争议
        }
    }
};
class Map {
  private:
    // vector storing vertices in the map: id of each vertex = index in vector
    vector<Vertex*> vertices;

    // Map: name of vertex -> id of vertex = index storing vertex ptr
    unordered_map<string, unsigned int> vertexId;

    // Directed edge in vector represents an undirected edge used in MST
    vector<Edge*> undirectedEdges;
    float infinityDist = 99999;
    /*
     * Add a vertex with name and x, y coordinates to the map graph. Returns
     * false if the name already existed in the map graph, and true otherwise
     */
    bool addVertex(const string& name, float x, float y);

    /*
     * Add an undirected edge between vertices with names "name1" and "name2".
     * Returns false if either name is not in the map graph.
     */
    bool addEdge(const string& name1, const string& name2);
    bool BfsHelper(Vertex* start, Vertex* End);
    Edge* RemoveEdge(Vertex* start, Vertex* end);
    void RestoreEdge(Vertex* start, Edge* edge);
    /**
     * Used for findMST(), given a vertice, check if we can find it in the
     * up-tree. If we can find it in the up-tree, then means it is in the same
     * set; otherwise, call union()
     */
    Vertex* find(Vertex* vertex);
    /**Used for findMST(), given two vertices(sentinals), we can use their
     * children in their own up-trees.
     */
    void Union(Vertex* v1, Vertex* v2);
    void Dreset();

  public:
    /* TODO: Initialize an empty map */
    Map();

    /* Build the map graph from vertex and edge files */
    bool buildMapFromFile(const string& vertexFileName,
                          const string& edgeFileName);

    /* TODOGiven two cities' names, we can find the corresponding vertices in
     * the map, and use priority queue to store each vertice's neighbors and
     * their weights. By using pq, we can sort the weights, ans find the
     * shortest weight between two vertices.
     */
    void Dijkstra(const string& from, const string& to,
                  vector<Vertex*>& shortestPath);

    /* TODO:Traverse the vector that full of all the edge nodes in the graph,
     * For each edge node, check if its source vertex and target vertex are in
     * the same set, if not, union them; otherwise, ignore this edge.
     */
    void findMST(vector<Edge*>& MST);

    /* TODO */
    void crucialRoads(vector<Edge*>& roads);

    /* Destructor of Map graph */
    ~Map();
};

#endif  // Map_HPP