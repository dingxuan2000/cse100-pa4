/**
 * TODO: add file header
 */

#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/* TODO
 * 在pathfinder.cpp里面，create a ActorGraph pointer,
 * 现在需要给这个graph里面的什么initialize 我觉得是actor node(vertice), movie
 * node(edge)需要initialize, 但是不确定这样initialize map，对吗？
 */
ActorGraph::ActorGraph() : ActorMap(0), MovieMap(0) {}
void ActorGraph::build(string actor, string title, int year,
                       string title_year) {
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
        }
    }
}
/* Build the actor graph from dataset file.
 * Each line of the dataset file must be formatted as:
 * ActorName <tab> MovieName <tab> Year
 * Two actors are connected by an undirected edge if they have worked in a movie
 * before.
 * 这里的filename就比如是data/imdb_2019.tsv
 */
bool ActorGraph::buildGraphFromFile(const char* filename) {
    //和open
    // function用法一样，这样更简单，直接创建对象，创建对象的过程直接调用open
    //方法
    ifstream infile(filename);
    bool readHeader = false;

    // after it extracts the last bit of the infile data, then will reach EOF,
    // then tederminate the loop
    while (infile) {
        string s;
        //这里没懂，getline returns iostream
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

/* TODO */
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
                    //     // if the actor node in this movie vector has not
                    //     been
                    //     // visited, then visit it, reset its dist, its
                    //     visited, its
                    //     // prev(should be current movie node's prev:the last
                    //     actor
                    //     // node), and last push into queue
                    ActorNode* ptr = *it;
                    if (ptr->visited == false) {
                        ptr->visited = true;
                        ptr->dist = p->dist + 1;
                        ptr->prev = p;
                        toExplore.push(ptr);
                    }
                    //     // if the actor node has already visited, do nothing
                }
            }
            // if the movie node has already visited, do nothing
        }
    }
    ActorNode* end = ActorMap[toActor];
    while (end != 0) {
        shortestPath = "(" + end->actorName + ")" + shortestPath;
        if (end->prev != 0) {
            shortestPath = end->prev->MovieYear + shortestPath;
            end = end->prev->prev;
        } else {
            // shortestPath = "(" + end->actorName + ")" + shortestPath;
            break;
        }
    }
}
/* TODO */
void ActorGraph::predictLink(const string& queryActor,
                             vector<string>& predictionNames,
                             unsigned int numPrediction) {}

/* TODO */
ActorGraph::~ActorGraph() {}
