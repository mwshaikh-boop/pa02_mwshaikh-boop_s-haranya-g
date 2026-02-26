#ifndef MOVIES_H
#define MOVIES_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Movie{
  private:
    string title;
    double rating;
  public:
    Movie(string t, double r);
    string getTitle() const;
    double getRating() const;
    bool operator>(const Movie& other) const;
    bool operator<(const Movie& other) const;

};

class MovieCollection{
  private:
    vector<Movie> movies;
    double highestRating;
    string highestTitle;
  public:
    void insert(const string& title, double rating);
    void sortByTitle();
    void sortByRating();
    void printAll();
    void findPrefix(const string& prefix);
    vector<Movie>& getMovies();
    double getHighestRating() const;
    string getHighestTitle() const;
};

bool comp(const Movie& a, const Movie& b);

#endif
