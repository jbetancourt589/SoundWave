#pragma once
#include <vector>
#include <string>
#include "Song.h"

// reads the spotify csv and returns a list of songs
std::vector<Song> loadCSV(const std::string& filename);