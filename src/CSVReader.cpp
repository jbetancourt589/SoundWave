#include "../include/CSVReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// some songs have commas in their names so we gotta handle that
string parseField(stringstream& ss) {
    string field;
    if (ss.peek() == '"') {
        ss.ignore(); // skip the opening quote
        getline(ss, field, '"'); // read until closing quote
        ss.ignore(); // skip comma after
    } else {
        getline(ss, field, ',');
    }
    return field;
}

vector<Song> loadCSV(const string& filename) {
    vector<Song> songs;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "couldnt open the file: " << filename << endl;
        return songs;
    }

    string line;
    getline(file, line); // skip the header row

    while (getline(file, line)) {
        stringstream ss(line);

        string col0, col1, artists, col3, track_name, popularityStr;

        getline(ss, col0, ',');   // col 0: index number
        getline(ss, col1, ',');   // col 1: track id
        artists = parseField(ss); // col 2: artist name
        col3 = parseField(ss);    // col 3: album name
        track_name = parseField(ss); // col 4: song name
        getline(ss, popularityStr, ','); // col 5: popularity

        if (popularityStr.empty()) continue;

        try {
            int popularity = stoi(popularityStr);
            songs.push_back(Song(track_name, artists, popularity));
        } catch (...) {
            continue; // skip any bad rows
        }
    }

    cout << "Loaded " << songs.size() << " songs.\n";
    return songs;
}