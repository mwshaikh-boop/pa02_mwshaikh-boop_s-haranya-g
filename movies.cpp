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
    vector<Movie> result;
    highestRating = -1;
    highestTitle = "";
    int size = prefix.length();
    Movie burner(prefix, 0);
    auto it = lower_bound(movies.begin(), movies.end(), burner);
    while(it != movies.end()){
      //++it;	    
      if(it->getTitle().compare(0, size, prefix) != 0) break;
      result.push_back(*it);

      if(it->getRating() > highestRating || (it->getRating() == highestRating && it->getTitle() < highestTitle)){
	      highestRating = it->getRating();
	      highestTitle = it->getTitle();
      }
      ++it;
    }
    sort(result.begin(), result.end(), comp);
    MovieCollection resultCol;
    resultCol.getMovies() = result;
    resultCol.printAll();
}

bool comp(const Movie& a, const Movie& b){
  if(a.getRating() == b.getRating()) return a.getTitle() < b.getTitle();
  return a.getRating() > b.getRating();
}
