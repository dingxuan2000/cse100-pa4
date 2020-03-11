#ifndef EDGE_HPP
#define EDGE_HPP

#include <math.h>
#include <string>
#include <vector>
#include "Vertex.hpp"

using namespace std;

class Vertex;

/* This class defines a directed edge from source vertex to target vertex in the
 * map graph */
class Edge {
  public:
    Vertex* source;
    Vertex* target;
    float weight;  // the Euclidean distance between source and target vertices

    /* The constructor that creates a new edge */
    Edge(Vertex* source, Vertex* target, float weight)
        : source(source), target(target), weight(weight) {}

    bool operator<(Edge w2) { return (this->weight < w2.weight); }

    bool operator>(Edge w2) { return (this->weight > w2.weight); }
};

#endif  // EDGE_HPP