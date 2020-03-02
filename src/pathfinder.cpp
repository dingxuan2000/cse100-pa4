/**
 * CSE 100 PA4 Pathfinder in Actor Graph
 */
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>  //用于使用istringstream
#include <string>
#include <vector>
#include "ActorGraph.hpp"

using namespace std;

/* Print the usage of the program */
void usage(char* program_name) {
    cerr << program_name << " called with incorrect arguments." << endl;
    cerr << "Usage: " << program_name
         << " movie_cast_file actor_pairs_file shortest_paths_file" << endl;
}

/* Main program that drives the pathfinder */
int main(int argc, char* argv[]) {
    const int NUM_ARG = 4, INPUT_IDX = 1, PAIR_IDX = 2, OUT_IDX = 3,
              PAIR_SIZE = 2;

    if (argc != NUM_ARG) {
        usage(argv[0]);
        return 1;
    }

    char* graphFileName = argv[INPUT_IDX];
    char* pairs = argv[PAIR_IDX];
    char* output = argv[OUT_IDX];

    // build the actor graph from the input file
    ActorGraph* graph = new ActorGraph();
    cout << "Reading " << graphFileName << " ..." << endl;
    if (!graph->buildGraphFromFile(graphFileName)) return 1;
    cout << "Done." << endl;

    /*---Testing buildGraph functions!-----*/
    // cout << graph->ActorMap["James McAvoy"]->actorName << endl;
    // int vector_size =
    //     graph->MovieMap["The Current War2017"]->actor_vector.size();
    // cout << graph->MovieMap["The Current War2017"]->year << endl;
    // for (int i = 0; i < vector_size; i++) {
    //     cout << graph->MovieMap["The Current War2017"]
    //                 ->actor_vector[i]
    //                 ->actorName
    //          << endl;
    // }
    /*--------------------------*/

    // write the shorest path of each given pair to the output file
    ifstream infile(pairs);
    ofstream outfile(output);
    bool haveHeader = false;

    while (infile) {
        string s;
        if (!getline(infile, s)) break;

        // skip reading the header in inFile and output the header in outFile
        if (!haveHeader) {
            outfile << "(actor)--[movie#@year]-->(actor)--..." << endl;
            haveHeader = true;
            continue;  // jump out this time's while loop, 接着第二次的while
                       // loop,从第二次的
            // while loop,
            // 就会skip这个if条件，因为haveHeader已经被设置成true了！
        }

        // read the pair from each line
        istringstream ss(s);  //这个s是inFile里面每一行的string
        vector<string> actorPair;
        // this while reads two substrings from each row's whole string:ss
        while (ss) {
            string str;
            // istream& getline (char* s, streamsize n, char delim );
            // use '\t' to be a delimiter, 遇到'\t',就停止继续read
            // which我们一次读一个actor's name,所以一次call
            // getline(),就可以存一个actor'name into str
            if (!getline(ss, str, '\t')) break;
            //一次while loop, push一个actor's name into this actorPair vector!
            actorPair.push_back(str);
        }

        // skip the incorrectly formatted line in input file
        if (actorPair.size() != PAIR_SIZE) {
            continue;
        }

        string actor1(actorPair[0]);
        string actor2(actorPair[1]);

        // output the shorest path for each line
        string shortestPath = "";
        graph->BFS(actor1, actor2, shortestPath);

        if (shortestPath.length() > 0) {
            outfile << shortestPath;
        }
        outfile << endl;
    }
    outfile.close();
    infile.close();
    delete graph;
    return 0;
}
