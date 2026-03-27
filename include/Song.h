#pragma once
#include <string>

struct Song {
    std::string track_name;
    std::string artists;
    int popularity;

    // this struct holds all the info for one song
    Song(std::string name, std::string artist, int pop) {
        track_name = name;
        artists = artist;
        popularity = pop;
    }

    //  needed this for when we create an empty song
    Song() {
        track_name = "";
        artists = "";
        popularity = 0;
    }
};