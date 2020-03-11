#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>
#include <vector>

using namespace std;

class Edge;

/* This class defines a vertex in map graph. Each vertex has a name and x, y
 * coordinates in the map */
class Vertex {
  public:
    const string name;
    float x;
    float y;
    vector<Edge*> outEdges;  // the adjacency list of this vertex that contains
                             // all outgoing edges

    // TODO: you may add more member variables here
    float weight;  // the distance of current vertex
    bool done;     // test if this vertex has been visited
    Vertex* prev;  // the current Vertex's previous node

    int count_child = 0;       // count the number of children of a sentinal
    Vertex* parent = nullptr;  // determine the parent of each vertex in up-tree
    /* The constructor that creates a new vertex */
    Vertex(const string& name, float x, float y) : name(name), x(x), y(y) {}
};

#endif  // VERTEX_HPP