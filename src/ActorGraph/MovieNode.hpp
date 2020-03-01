/**
 * TODO: file header
 *
 * Author:Xuan Ding, xding@ucsd.edu
 *        Qilong Li, qil009@ucsd.edu
 *
 */
#ifndef MOVIENODE_HPP
#define MOVIENODE_HPP
#include <iostream>
#include <vector>
#include "ActorNode.hpp"
using namespace std;

class MovieNode {
  private:
  public:
    string movie_name;  // the name of the movie
    int movie_year;     // the year of the movie
    // a vector to store the other actors pointers
    // that also participant in this movie
    vector<ActorNode*> actors;

    // create a pair to store movie name and movie year
    // pair<string, int> moviePair;
    // moviePair.first = movie_name;
    // moviePair.second = movie_year;
    /* Constructor that initialize a MovieNode */
    MovieNode(string name, int year) : movie_name(name), movie_year(year) {}
};

#endif