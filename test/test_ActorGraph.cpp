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
    // cout << "Reading " << graphFileName << " ..." << endl;
    // cout << graph->buildGraphFromFile(graphFileName) << endl;
    // graph->buildGraphFromFile("data/small_actor_graph.tsv");
    // ActorNode* ptr = graph->ActorMap["Kevin Bacon"];
    // ASSERT_EQ(ptr, nullptr);
    // cerr << ptr << endl;

    // cout << "Done." << endl;
    graph->build("Alice", "007", 2002, "007#2002");
    cout << graph->ActorMap["Alice"] << endl;
}