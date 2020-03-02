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
    // ASSERT_EQ(graph->ActorMap["Alice"]->actorName, "Alice");
    // ASSERT_EQ(graph->ActorMap["Alice"]->movies_vector[0]->MovieName, "007");
    graph->build("John", "0071", 2002, "00712002");
    graph->build("Berry", "0071", 2002, "00712002");
    // ASSERT_EQ(graph->MovieMap["00712002"]->MovieName, "0071");
    // ASSERT_EQ(graph->MovieMap["00712002"]->year, 2002);
    // ASSERT_EQ(graph->MovieMap["00712002"]->actor_vector.size(), 2);
    graph->build("Berry", "0072", 2002, "00722002");
    graph->build("Berry", "0072", 2002, "00722002");
    // ASSERT_EQ(graph->ActorMap["Berry"]->movies_vector.size(), 2);
    // ASSERT_EQ(graph->MovieMap["00722002"]->actor_vector.size(), 1);

    // cerr << graph->ActorMap["Alice"]->actorName << endl;
}
// TEST(SimpleGraph, TEST_BFS){

// }