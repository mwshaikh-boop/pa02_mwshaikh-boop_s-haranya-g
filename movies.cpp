#include "movies.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

Movie::Movie(string t, double r) : title(t), rating(r) {}

string Movie::getTitle() const{
  return title;
}

double Movie::getRating() const{
  return rating;
}

bool Movie::operator>(const Movie& other) const{
  return title > other.getTitle();
}

bool Movie::operator<(const Movie& other) const{
  return title < other.getTitle();
}

void MovieCollection::insert(const string& title, double rating){
  movies.push_back({title, rating});
}

void MovieCollection::sortByTitle(){
  sort(movies.begin(), movies.end());
}

void MovieCollection::printAll(){
  //sortByTitle();
  for (Movie &m : movies){
    cout << m.getTitle() << ", " << m.getRating() << endl;
  } 
}

vector<Movie>& MovieCollection::getMovies(){
  return movies;
}

double MovieCollection::getHighestRating() const{
  return highestRating;
}

string MovieCollection::getHighestTitle() const{
  return highestTitle;
}

void MovieCollection::findPrefix(const string& prefix){
    MovieCollection result;
    highestRating = -1;
    highestTitle = "";
    int size = prefix.length();
    for (Movie &m : movies){
      if(m.getTitle().substr(0, size) == prefix){
	    result.insert(m.getTitle(), m.getRating());
	    if(m.getRating() > highestRating || (m.getRating() == highestRating && m.getTitle() < highestTitle)){
	      highestRating = m.getRating();
	      highestTitle = m.getTitle();
	    }
      }
    } 
    sort(result.getMovies().begin(), result.getMovies().end(), comp);
    result.printAll();
}

bool comp(const Movie& a, const Movie& b){
  if(a.getRating() == b.getRating()) return a.getTitle() < b.getTitle();
  return a.getRating() > b.getRating();
}
