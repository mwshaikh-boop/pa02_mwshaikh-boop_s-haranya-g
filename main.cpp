// Winter'24
// Instructor: Diba Mirza
// Student name: Mu'aaz Shaikh, Sharanya Garudathil 
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies
    
    MovieCollection movieList;
    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout << movieName << " has rating " << movieRating << endl;
            // insert elements into your data structure
            movieList.insert(movieName, movieRating);
    }
    
    movieList.sortByTitle();
    movieFile.close();

    if (argc == 2){
            //print all the movies in ascending alphabetical order of movie names
	    movieList.sortByTitle();
	    movieList.printAll();
            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    vector<double> highestRatings;
    vector<string> highestNames;
    vector<string> prefixExists;
    for(string prefix: prefixes){
      movieList.findPrefix(prefix);
      if(movieList.getHighestRating() != -1){
        highestRatings.push_back(movieList.getHighestRating());
        highestNames.push_back(movieList.getHighestTitle());
	prefixExists.push_back(prefix);
	cout << endl;
      } else{
        cout << "No movies found with prefix "<< prefix << endl;
      }
    }
    if(prefixes.empty()){
      cout << "No movies found with prefix "<<"<replace with prefix>" << endl;
    }

    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    for(int i = 0; i < prefixExists.size(); i++){
    cout << "Best movie with prefix " << prefixExists[i] << " is: " << highestNames[i] << " with rating " << std::fixed << std::setprecision(1) << highestRatings[i] << endl;
    }

    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}
