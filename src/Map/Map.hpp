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
    Vertex* find(Vertex* vertex);
    void Union(Vertex* v1, Vertex* v2);
    void Dreset();

  public:
    /* TODO */
    Map();

    /* Build the map graph from vertex and edge files */
    bool buildMapFromFile(const string& vertexFileName,
                          const string& edgeFileName);

    /* TODO */
    void Dijkstra(const string& from, const string& to,
                  vector<Vertex*>& shortestPath);

    /* TODO */
    void findMST(vector<Edge*>& MST);

    /* TODO */
    void crucialRoads(vector<Edge*>& roads);

    /* Destructor of Map graph */
    ~Map();
};

#endif  // Map_HPP