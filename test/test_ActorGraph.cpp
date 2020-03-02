#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <sstream>  //用于使用istringstream
#include <string>
#include <vector>
using namespace std;
using namespace testing;
#include "ActorGraph.hpp"
// TODO: add tests for actor graph
// shouldn't read any files!!!
TEST(SimpleGraph, TEST_BUILD) {
    ActorGraph* graph = new ActorGraph();
    graph->build("Alice", "007", 2002, "0072002");
    graph->build("Alice", "007", 2003, "0072003");
    ASSERT_EQ(graph->ActorMap["Alice"]->actorName, "Alice");
    ASSERT_EQ(graph->ActorMap["Alice"]->movies_vector[0]->MovieName, "007");
    graph->build("John", "0071", 2002, "00712002");
    graph->build("Berry", "0071", 2002, "00712002");
    ASSERT_EQ(graph->MovieMap["00712002"]->MovieName, "0071");
    ASSERT_EQ(graph->MovieMap["00712002"]->year, 2002);
    ASSERT_EQ(graph->MovieMap["00712002"]->actor_vector.size(), 2);
    graph->build("Berry", "0072", 2002, "00722002");
    ASSERT_EQ(graph->ActorMap["Berry"]->movies_vector.size(), 2);
    ASSERT_EQ(graph->MovieMap["00722002"]->actor_vector.size(), 1);
    graph->build("John", "0072", 2002, "00722002");
    ASSERT_EQ(graph->MovieMap["00722002"]->actor_vector.size(), 2);
    ASSERT_EQ(graph->ActorMap["John"]->movies_vector.size(), 2);

    // cerr << graph->ActorMap["Alice"]->actorName << endl;
    string shortPath1 = "";
    graph->BFS("John", "Berry", shortPath1);
    // cout << shortPath << endl;
    EXPECT_EQ("(John)--[0071#@2002]-->(Berry)", shortPath1);
    string shortPath2 = "";
    graph->BFS("Alice", "John", shortPath2);
    EXPECT_EQ("", shortPath2);

    string shortPath3 = "";
    graph->BFS("Alice", "Alice", shortPath3);
    EXPECT_EQ("", shortPath3);

    string shortPath4 = "";
    graph->BFS("Alice2", "Alice", shortPath4);
    EXPECT_EQ("", shortPath4);
    delete graph;
}
TEST(SimpleGraph, TEST_READFILE) {
    ActorGraph* graph = new ActorGraph();
    graph->buildGraphFromFile("buildGraph.txt");
    ifstream infile("buildGraph.txt");
    bool readHeader = false;
    while (infile) {
        string s;
        if (!getline(infile, s)) break;

        if (!readHeader) {
            readHeader = true;
            continue;
        }
        istringstream ss(s);
        vector<string> record;
        while (ss) {
            string str;
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        if (record.size() != 3) {
            continue;
        }

        string actor(record[0]);
        string title(record[1]);
        string title_year(record[1] + record[2]);
        int year = stoi(record[2]);

        graph->build(actor, title, year, title_year);
    }

    if (!infile.eof()) {
        cerr << "Failed to read "
             << "buildGraph.txt" << endl;
    }
    infile.close();
}