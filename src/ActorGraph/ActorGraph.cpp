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
        int year = stoi(record[2]);

        // create a pair to store movie name and movie year
        pair<string, int> moviePair;
        moviePair.first = title;
        moviePair.second = year;
        // TODO: we have an actor/movie relationship to build the graph
        // 1.先判断ActorMap里面有没有一样的actor, 如果没有，需要create a new
        // node, assign this new node some values:
        // Note: count() returns 1 if the element with key K is present in the
        // map cotainer; otherwise, returns 0 if the element with key K is not
        // present in the map.
        if (this->ActorMap.count(actor) == 0) {
            // create a new actor node, and push into ActorMap
            ActorNode* newactor = new ActorNode(actor);
            ActorMap.insert({actor, newactor});
            // check if the movie node is not in MovieMap
            if (this->MovieMap.count(moviePair) == 0) {
                // create a movie node, and push into MovieMap,and push
                // into actor node's vector
                MovieNode* newmovie = new MovieNode(title, year);
                MovieMap.insert({moviePair, newmovie});
                newactor->movies.push_back(newmovie);
                newmovie->actors.push_back(newactor);
            }  // if move node is in MovieMap,不需要create node, 连线就好
            else {
                newactor->movies.push_back(MovieMap.at(moviePair));
                MovieMap.at(moviePair)->actors.push_back(newactor);
            }

        }  // else, insert the movie node into actor's vector
        else {
            // check if the movie node is not in MovieMap
            if (this->MovieMap.count(moviePair) == 0) {
                // create a movie node, and push into MovieMap
                MovieNode* newmovie = new MovieNode(title, year);
                MovieMap.insert({moviePair, newmovie});
                // need to connect the actor node and movie node
                ActorMap.at(actor)->movies.push_back(newmovie);
                newmovie->actors.push_back(ActorMap.at(actor));
            }  // if the movie node is alreay in map, do nothing
            else {
                continue;
            }
        }
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
                     string& shortestPath) {}

/* TODO */
void ActorGraph::predictLink(const string& queryActor,
                             vector<string>& predictionNames,
                             unsigned int numPrediction) {}

/* TODO */
ActorGraph::~ActorGraph() {}
