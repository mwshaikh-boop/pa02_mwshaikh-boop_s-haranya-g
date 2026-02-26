// Winter'24
// Instructor: Diba Mirza
// Student name: Mu'aaz Shaikh, Sharanya Garudathil 
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
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
    auto start = chrono::high_resolution_clock::now();

    vector<double> highestRatings;
    vector<string> highestNames;
    vector<string> prefixExists;
    // time complexity of for loop: O(m)
    for(string prefix: prefixes){
      // time complexity of findPrefix: O(logn + 1 + n + klogk)
      // space complexity of findPrefix: O(k)
      movieList.findPrefix(prefix);
      if(movieList.getHighestRating() != -1){
	// space complexity of highestRatings, highestNames, prefixExists vectors: O(m)
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
    // Total time complexity: m * (log(n) + 1 + n + klogk) = O(mlogn + m + mn + mklogk)
    // Total space complexity: m + k = O(m + k)

    // End timing
    auto end = chrono::high_resolution_clock::now();

    // Calculate duration in microseconds (as a double)
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    double time_taken = duration.count() / 1000.0;  // Convert to milliseconds
    
    //if (time_taken < 1.0) {
    //    cout << " Time : " << time_taken * 1000 << " microsec" << endl;  // Convert back to microsec if < 1ms
    //} else {
    //    cout << " Time : " << time_taken << " ms" << endl;
    //}
    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/

/* 
Worst-case Big-O time complexity: O(m log(n) + m + mn + mk log(k))
The for loop that takes out each of the prefixes in the vector prefixes will run for however many prefixes there are, or m times. Within that for loop, the function findPrefix is called, which doesn't have a constant time complexity. It uses lower_bound to assign a value to the iterator it, which has a time complexity of log(n) + 1. A while loop then runs until the iterator reaches the end, which has a worst case time complexity of n. Finally, this function uses sort, which has a runtime of klogk. This gives the findPrefix function a time complexity of O(log(n) + 1 + n + klog(k)). Everything else in this prefix and in the main function for part 2 (excluding the parts that print) have a constant time complexity. We can multiply m by the time complexity of findPrefix to get O(m log(n) + m + mn + mk log(k)).

input_20_random.csv runtime for prefix_large.txt: 31.8 ms
input_100_random.csv runtime for prefix_large.txt: 48.5 ms
input_1000_random.csv runtime for prefix_large.txt: 54.6 ms
input_76920_random.csv runtime for prefix_large.txt: 334.1 ms

Worst-case Big-O space complexity: O(m + k)
For part 2, we make 3 vectors called highestRatings, highestNames, and prefixExists, all of which can have a maximum size of however many prefixes there are, giving a space complexity of O(m). The function findPrefix also creates a vector called result, which can push into it at most k movies, or the max number of movies with each prefix, giving a space complexity of O(k). Therefore, the space complexity for part 2 is O(m + k).

We designed our algorithm to have a low time complexity, with our target complexity being less than O(n^2)
We were also able to achieve a low space complexity of O(m + k) since the space complexity is not dependent on the total number of movies (or n), but rather is only dependent on the number of prefixes and the maximum number of movies with each prefix.
*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}
