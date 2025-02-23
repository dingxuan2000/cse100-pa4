/**
 * TODO: add file header
 * Author:Xuan Ding, xding@ucsd.edu
 *        Qilong Li, qil009@ucsd.edu
 * this file provides  implementation of constructor and destructor of
 * ActorGraph class. as well as the implementation of functions in
 * ActorGraph.hpp.
 */

#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/* TODO
 * Initialize tow hashmaps to be empty initially.
 */
ActorGraph::ActorGraph() : ActorMap(0), MovieMap(0) {}
/*
 * Helper function: According to string actor, movieName, movieYear to
 * build the graph, using two hashmap: ActorMap, MovieMap to store the
 * actor nodes and movie nodes, then connect them by using vector in each node.
 */
void ActorGraph::build(const string& actor, const string& title,
                       const int& year, const string& title_year) {
    if (this->ActorMap.count(actor) == 0) {
        this->ActorMap[actor] = new ActorNode(
            actor);  // create a new actor node if no actor node is found
        if (this->MovieMap.count(title_year) == 0) {
            this->MovieMap[title_year] = new MovieNode(
                title, year);  // if movie is not added create movie node

            this->MovieMap[title_year]->addActor(
                this->ActorMap[actor]);  // movie adds actor
            this->ActorMap[actor]->addMovie(
                this->MovieMap[title_year]);  // actor adds movie.
        } else {                              // if movie is found.
            this->ActorMap[actor]->addMovie(
                this->MovieMap[title_year]);  // actor adds movie
            this->MovieMap[title_year]->addActor(
                this->ActorMap[actor]);  // movie adds actor
        }

    } else {                                          // if actor is found.
        if (this->MovieMap.count(title_year) == 0) {  // if movie is not found
            this->MovieMap[title_year] = new MovieNode(title, year);
            this->MovieMap[title_year]->addActor(
                this->ActorMap[actor]);  // movie adds actor
            this->ActorMap[actor]->addMovie(
                this->MovieMap[title_year]);  // actor adds movie.
        } else {
            this->MovieMap[title_year]->addActor(
                this->ActorMap[actor]);  // movie adds actor
            this->ActorMap[actor]->addMovie(
                this->MovieMap[title_year]);  // actor adds movie.
        }
    }
}
/* Build the actor graph from dataset file.
 * Each line of the dataset file must be formatted as:
 * ActorName <tab> MovieName <tab> Year
 * Two actors are connected by an undirected edge if they have worked in a movie
 * before.
 * Here, call helper function build() to build the graph
 */
bool ActorGraph::buildGraphFromFile(const char* filename) {
    // same as open function, easier:can create object directly
    ifstream infile(filename);
    bool readHeader = false;

    // after it extracts the last bit of the infile data, then will reach EOF,
    // then tederminate the loop
    while (infile) {
        string s;
        // Confused here:getline returns iostream
        if (!getline(infile, s)) break;

        // skip the header of the file
        if (!readHeader) {
            readHeader = true;
            continue;  // will skip the whole loopdealing with the first line
                       // information
        }

        // s: get the whole string in a row, until reaches newline
        // read each line of the dataset to get the movie actor relation
        istringstream ss(s);  // istringstream: helps to deliminate the whole
                              // string to substrings, so here, ss is still the
                              // same as s, which is the whole string in a row.
        vector<string> record;
        while (ss) {
            string str;
            if (!getline(ss, str, '\t')) break;
            // in this while loop, push three strings: actor name, movie name
            // movie year into record vector
            record.push_back(str);
        }

        // if format is wrong, skip current line
        if (record.size() != 3) {
            continue;
        }

        // extract the information
        string actor(record[0]);
        string title(record[1]);
        string title_year(record[1] + record[2]);
        int year = stoi(record[2]);

        build(actor, title, year, title_year);

        // TODO: we have an actor/movie relationship to build the graph
    }

    // if failed to read the file, clear the graph and return
    if (!infile.eof()) {
        cerr << "Failed to read " << filename << endl;
        return false;
    }
    infile.close();

    return true;
}
/*
 * resetBFS This function resets the varible prev, and  visited to default for
 * each node of the graph
 */
void ActorGraph::Bfsreset() {
    unordered_map<string, ActorNode*>::iterator iter1 = ActorMap.begin();
    unordered_map<string, MovieNode*>::iterator iter2 = MovieMap.begin();

    for (; iter1 != ActorMap.end(); ++iter1) {
        ActorNode* ptr = iter1->second;
        ptr->visited = false;
        ptr->prev = nullptr;
    }
    for (; iter2 != MovieMap.end(); ++iter2) {
        MovieNode* ptr = iter2->second;
        ptr->visited = false;
        ptr->prev = nullptr;
    }
}
/* TODO
 * This function performs breath first search to the graph. This function takes
 three strings as parameter, string fromActor is the actor name of the graph
 starting from, string toActor is is the destination of the graph. The paths
 from starting node to destination node will be written into the string
 shortestPath.
*/
void ActorGraph::BFS(const string& fromActor, const string& toActor,
                     string& shortestPath) {
    if (fromActor == toActor) {
        shortestPath = "";
        return;
    }
    if (this->ActorMap.count(fromActor) == 0 ||
        this->ActorMap.count(toActor) == 0) {
        shortestPath = "";
        return;
    }
    queue<ActorNode*> toExplore;
    ActorNode* start = ActorMap[fromActor];
    start->dist = 0;
    // start->prev = nullptr;
    toExplore.push(start);  // push the start actor node into the queue
    // if the actor2 has not been visited, then continue traver the graph
    while ((ActorMap[toActor]->visited == false) && (!toExplore.empty())) {
        ActorNode* next = toExplore.front();  // front() just returns a
                                              // reference to the first
        // element of the vector
        toExplore.pop();  // first. pop a node in queue

        // begin() returns an iterator that can be used to iterate throught the
        // vector
        // 1.traverse the movie nodes in the current actor node's movie
        // vector
        vector<MovieNode*>::iterator iter = next->movies_vector.begin();
        for (; iter != next->movies_vector.end(); ++iter) {
            // if the current movie node has not been visited, then visit it
            MovieNode* p = *iter;
            if (p->visited == false) {
                // cout << p->MovieName << endl;
                p->visited = true;
                p->dist = next->dist;
                p->prev = next;
                // then push all the actor node's neighbors into
                // queue(toExplore) by traversing current movie node's actor
                // vector
                vector<ActorNode*>::iterator it = p->actor_vector.begin();
                for (; it != p->actor_vector.end(); ++it) {
                    // if the actor node in this movie vector has not been
                    // visited, then visit it, reset its dist, its visited,
                    // its prev(should be current movie node's prev:the
                    // lastactor node), and last push into queue
                    ActorNode* ptr = *it;
                    if (ptr->visited == false) {
                        ptr->visited = true;
                        ptr->dist = p->dist + 1;
                        ptr->prev = p;
                        toExplore.push(ptr);
                    }
                    // if the actor node has already visited, do nothing
                }
            }
            // if the movie node has already visited, do nothing
        }
    }
    ActorNode* end = ActorMap[toActor];
    if (end->visited == false) {
        Bfsreset();
        return;
    }
    // start->prev = nullptr;
    while (end != start) {
        // cout << end->actorName << endl;
        shortestPath = "(" + end->actorName + ")" + shortestPath;
        // cout << end->prev->MovieYear << endl;
        if (end != nullptr) {
            // cout << end->prev->MovieName << endl;
            shortestPath = end->prev->MovieYear + shortestPath;
            end = end->prev->prev;

        } else {
            break;
        }
    }
    Bfsreset();
    shortestPath = "(" + start->actorName + ")" + shortestPath;
}
/* TODO */
void ActorGraph::predictLink(const string& queryActor,
                             vector<string>& predictionNames,
                             unsigned int numPrediction) {}

/* TODO
 * Delete all actor nodes and movie nodes in two hashmaps
 */
ActorGraph::~ActorGraph() {
    unordered_map<string, ActorNode*>::iterator iter1 = ActorMap.begin();
    unordered_map<string, MovieNode*>::iterator iter2 = MovieMap.begin();

    for (; iter1 != ActorMap.end(); ++iter1) {
        ActorNode* ptr = iter1->second;
        delete ptr;
    }
    for (; iter2 != MovieMap.end(); ++iter2) {
        MovieNode* ptr = iter2->second;
        delete ptr;
    }
}
