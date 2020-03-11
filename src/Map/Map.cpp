
#include "Map.hpp"

/* TODO */
Map::Map() {}

/* Build the map graph from vertex and edge files */
bool Map::buildMapFromFile(const string& vertexFileName,
                           const string& edgeFileName) {
    // add vertices first
    ifstream vertexFile(vertexFileName);
    while (vertexFile) {
        string s;
        if (!getline(vertexFile, s)) break;

        // process data at each line
        istringstream ss(s);
        vector<string> data;
        while (ss) {
            string str;
            if (!getline(ss, str, ' ')) break;
            data.push_back(str);
        }
        if (data.size() != 3) continue;

        // add vertex defined in this line to the graph
        string name(data[0]);
        float x = stoi(data[1]);
        float y = stoi(data[2]);

        addVertex(name, x, y);
    }

    // then add edges
    ifstream edgeFile(edgeFileName);
    while (edgeFile) {
        string s;
        if (!getline(edgeFile, s)) break;

        // process data at each line
        istringstream ss(s);
        vector<string> data;
        while (ss) {
            string str;
            if (!getline(ss, str, ' ')) break;
            data.push_back(str);
        }
        if (data.size() != 2) continue;

        // add edge defined in this line to the graph
        string name1(data[0]);
        string name2(data[1]);

        addEdge(name1, name2);
    }

    return true;
}

/*
 * Add a vertex with name and x, y coordinates to the map graph. Returns
 * false if the name already existed in the map graph, and true otherwise
 */
bool Map::addVertex(const string& name, float x, float y) {
    if (vertexId.count(name) > 0) return false;
    vertexId[name] = vertices.size();
    vertices.push_back(new Vertex(name, x, y));
    return true;
}

/*
 * Add an undirected edge between vertices with names "name1" and "name2".
 * Returns false if either name is not in the map graph.
 */
bool Map::addEdge(const string& name1, const string& name2) {
    if (vertexId.count(name1) == 0 || vertexId.count(name2) == 0) {
        return false;
    }
    unsigned int id1 = vertexId[name1];
    unsigned int id2 = vertexId[name2];
    Vertex* v1 = vertices[id1];
    Vertex* v2 = vertices[id2];
    float weight = sqrt(pow(v1->x - v2->x, 2) + pow(v1->y - v2->y, 2));
    v1->outEdges.push_back(new Edge(v1, v2, weight));
    v2->outEdges.push_back(new Edge(v2, v1, weight));

    undirectedEdges.push_back(new Edge(v1, v2, weight));
    return true;
}
// Initialize PQ: set
void Map::Dreset() {
    // traverse all the vertexes in the vector(vertices)
    vector<Vertex*>::iterator iter1 = vertices.begin();
    // set each vertex pointer: dist(weight) to be infinity, prev to be nullptr
    // done to be false.
    for (; iter1 != vertices.end(); ++iter1) {
        auto* ptr = *iter1;
        ptr->done = false;
        ptr->weight = infinityDist;
        ptr->prev = 0;
    }
}
/* TODO */
void Map::Dijkstra(const string& from, const string& to,
                   vector<Vertex*>& shortestPath) {
    // cout<<"started"<<endl;
    // edge case1
    if (from == to) {
        return;
    }
    // edge case2
    if (vertexId.count(from) == 0 || vertexId.count(to) == 0) {
        return;
    }
    // initialize the graph
    Dreset();  // reset graph

    Vertex* start = vertices[vertexId[from]];
    Vertex* end = vertices[vertexId[to]];
    // cout<< start->name;
    priority_queue<pair<Vertex*, int>, vector<pair<Vertex*, int>>, cmpVertex>
        pq;

    start->weight = 0;  // set the start vertex's dist to be 0

    pq.push(make_pair(start, 0));  // push the start vertex into the pq
    //最好改一下这里，只要当所以vertex vistited了之后，就可以停止pop pq了
    //所以可以加个count variable,记录一共多少vertices in the map,
    //每pop一个vertice, count--,知道count =0, stop poping from pq.
    while (!pq.empty()) {
        pair<Vertex*, int> top_pair = pq.top();
        Vertex* next = top_pair.first;
        if (top_pair.second < next->weight) {
            next->weight = top_pair.second;
        }
        next->done =
            true;  //这里好像有问题，还没pop, 就set done to be true，好像
        //不符合算法的步骤，应该先pop，再set true
        pq.pop();

        vector<Edge*>::iterator iter = next->outEdges.begin();

        for (; iter != next->outEdges.end(); ++iter) {
            Edge* edgeptr = *iter;
            Vertex* ptr = edgeptr->target;
            float newWeight = (edgeptr->source->weight) + (edgeptr->weight);
            if (newWeight < (ptr->weight))  // if new distance is less.
            {
                ptr->weight = newWeight;      // set new dist for next vertex
                ptr->prev = edgeptr->source;  // set prev for next vertex
                pq.push(make_pair(ptr, newWeight));  // push into the pq
            }

        }  // for
    }      // while
    // case: when target city has no connection to start city, then target city
    //'s weight must still be infinity, then just return the empty vector
    if (end->weight == infinityDist) {
        return;
    }

    vector<Vertex*>::iterator it = shortestPath.begin();
    stack<Vertex*> reverse;
    // back track the current vertex's prev, store the vertex from target to
    // start into stack
    while (end != start) {
        reverse.push(end);
        if (end->prev != 0) {
            end = end->prev;
        }

        // cout<<"end of file"<<endl;
    }
    // until end == start, stop loop, then push start automatically
    reverse.push(start);
    // pop each vertex in the stack to shortestPath vector.
    // So, shortestPath vector stores the shortest path from start to target.
    while (!reverse.empty()) {
        Vertex* temp = reverse.top();
        shortestPath.push_back(temp);
        reverse.pop();
    }
}
Vertex* Map::find(Vertex* vertex) {
    Vertex* ptr = vertex;
    vector<Vertex*> vec;
    int count = 0;
    if (ptr->parent == nullptr) {
        if (ptr->count_child == 0) {
            ptr->count_child = ptr->count_child + 1;
        }
        return ptr;
    }
    while (ptr->parent != nullptr) {
        vec.push_back(ptr);
        count++;
        ptr = ptr->parent;
    }
    ptr->count_child = count + 1;  // used to compare two sets' size in union()

    // traverse vec
    for (int i = 0; i < vec.size(); i++) {
        Vertex* vertex = vec.back();
        vertex->parent = ptr;
        vec.pop_back();
    }
    return ptr;
}
void Map::Union(Vertex* v1, Vertex* v2) {
    if (v1->count_child > v2->count_child) {
        v2->parent = v1;
        v1->parent = nullptr;
        v1->count_child = v1->count_child + v2->count_child;
    } else if (v1->count_child < v2->count_child) {
        v1->parent = v2;
        v2->parent = nullptr;
        v2->count_child = v1->count_child + v2->count_child;
    } else {
        v1->parent = v2;
        v2->parent = nullptr;
        v2->count_child = v1->count_child + v2->count_child;
    }
}
/* TODO */
void Map::findMST(vector<Edge*>& MST) {
    // 1.put all the edges into priority queue, and sort it from smallest to
    // largest
    priority_queue<pair<Edge*, float>, vector<pair<Edge*, float>>, cmpEdge> pq;
    vector<Edge*>::iterator iter = undirectedEdges.begin();
    for (; iter != undirectedEdges.end(); iter++) {
        Edge* edgeptr = *iter;
        pq.push(make_pair(edgeptr, edgeptr->weight));
    }

    // 2.每pop一个edge出来，首先看这个edge的两个vertex,
    // 通过find()查看这两个vertex是否 在同一个set里面，if they are not in the
    // same set, then union them.
    while (!pq.empty()) {
        Edge* edge = pq.top().first;

        Vertex* start = edge->source;  // get two sides of one edge
        Vertex* end = edge->target;
        // check each city, by find() to see if they are in the same set,
        // find() returns Vertex pointer
        // if they are in the same set(if find() returns two same vertex
        // pointer), which causes a cycle, so ignore this edge, 去看下一个edge
        Vertex* v1 = find(start);
        Vertex* v2 = find(end);

        if (v1 != v2) {
            // merge these two sets
            Union(v1, v2);
            MST.push_back(edge);
        }

        // Otherwise, if they are in the different set, then union them

        pq.pop();
    }
}

bool Map::BfsHelper(Vertex* start, Vertex* End) {
    Dreset();  // reset graph
    queue<Vertex*> ToExplore;
    Edge* temp = RemoveEdge(start, End);  // remove one edge and store to temp.
    ToExplore.push(start);
    while (End->done == false && !ToExplore.empty()) {
        Vertex* next = ToExplore.front();
        ToExplore.pop();
        next->done = true;
        vector<Edge*>::iterator iter = next->outEdges.begin();
        for (; iter != next->outEdges.end(); ++iter) {
            Edge* ptr = *iter;
            if (ptr->target->done == false) {
                ToExplore.push(ptr->target);

            }  // if

        }  // for

    }                          // while
    RestoreEdge(start, temp);  // add the removed edge back into vector.
    // If we can't reach the end vertex, then it has cricual edge between start
    // vertex and end vertex
    if (End->done == false) {  // bfs couldnt reach done.
        return true;
    }
    // if we can reach to end vertex, that means it's not a bridge edge
    // between these two vertices.
    else {
        return false;
    }
}  // bfs

Edge* Map::RemoveEdge(Vertex* start, Vertex* end) {
    for (int i = 0; i < start->outEdges.size(); i++) {
        Edge* edges = start->outEdges[i];
        Vertex* target = edges->target;
        if (target == end) {
            Edge* temp = edges;
            start->outEdges.erase(start->outEdges.begin() + i);
            return temp;
        }
    }
}

void Map::RestoreEdge(Vertex* start, Edge* edge) {
    start->outEdges.push_back(edge);
}
/* TODO */
void Map::crucialRoads(vector<Edge*>& roads) {
    vector<Edge*>::iterator iter = undirectedEdges.begin();
    for (; iter != undirectedEdges.end(); ++iter) {
        Edge* ptr = *iter;
        Vertex* start = ptr->source;
        Vertex* target = ptr->target;
        if (BfsHelper(start, target)) {  // if BFS return true then its bridge
            roads.push_back(ptr);
        }
    }
}

/* Destructor of Map graph */
Map::~Map() {
    for (Vertex* v : vertices) {
        for (Edge* e : v->outEdges) {
            delete e;
        }
        delete v;
    }
    for (Edge* e : undirectedEdges) {
        delete e;
    }
}
