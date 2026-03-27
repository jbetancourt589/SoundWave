# SoundMatch - Music Popularity Ranker

## Overview
SoundMatch compares two data structures — a Max Heap and a Splay Tree — to
retrieve the top-N most popular songs from a dataset of 114,000+ Spotify tracks.

## Team
- Nicolas Salazar — Max Heap + CSV Parser
- Jonathan Betancourt — Splay Tree
- Daniel Navas-Zurga — CLI Menu, Report, Video

## Requirements
- g++ with C++17 support

## Setup
1. Clone the repository:
   git clone https://github.com/jbetancourt589/SoundWave.git

2. Download the Spotify Tracks Dataset from Kaggle and place it in the data/ folder:
   https://www.kaggle.com/datasets/maharshipandya/-spotify-tracks-dataset
   Rename it to: spotify_tracks.csv

## How to Run
In the terminal, from the root SoundWave/ folder:

   g++ -std=c++17 -Iinclude src/main.cpp src/CSVReader.cpp src/MaxHeap.cpp src/SplayTree.cpp -o soundwave
   ./soundwave

## Features
1. Load the full 114,000+ song dataset from CSV
2. Get Top-N most popular songs using Max Heap
3. Get Top-N most popular songs using Splay Tree
4. Compare both structures side by side with build and query times
5. Exit

## Example Output
   Top 5 Songs (Max Heap):
   1. Blinding Lights - The Weeknd (100)
   2. Shape of You - Ed Sheeran (99)
   ...
   Build Time: 120 ms
   Query Time: 2 ms