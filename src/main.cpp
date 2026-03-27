#include <iostream>
#include <vector>
#include "../include/Song.h"
#include "../include/CSVReader.h"
#include "../include/MaxHeap.h"
#include "../include/SplayTree.h"

using namespace std;

void printSongs(const vector<Song>& songs) {
    for (int i = 0; i < (int)songs.size(); i++) {
        cout << i + 1 << ". " << songs[i].track_name
             << " - " << songs[i].artists
             << " (" << songs[i].popularity << ")\n";
    }
}

int main() {
    vector<Song> songs;
    MaxHeap heap;
    SplayTree tree;
    bool loaded = false;

    int choice;

    while (true) {
        cout << "\n==============================\n";
        cout << "  SoundMatch - Music Ranker\n";
        cout << "==============================\n";
        cout << "1. Load Dataset\n";
        cout << "2. Get Top-N Songs (Max Heap)\n";
        cout << "3. Get Top-N Songs (Splay Tree)\n";
        cout << "4. Compare Both Structures\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string path;
            cout << "Enter path to CSV file (or press Enter for default): ";
            cin.ignore();
            getline(cin, path);
            if (path.empty())
                path = "../data/spotify_tracks.csv";

            songs = loadCSV(path);
            if (songs.empty()) {
                cout << "No songs loaded. Check your file path.\n";
                continue;
            }

            cout << "Building Max Heap...\n";
            heap.buildHeap(songs);
            cout << "Max Heap built in " << heap.buildTime << " ms\n";

            cout << "Building Splay Tree...\n";
            tree.buildTree(songs);
            cout << "Splay Tree built in " << tree.buildTime << " ms\n";

            loaded = true;

        } else if (choice == 2) {
            if (!loaded) { cout << "Please load the dataset first!\n"; continue; }
            int n;
            cout << "Enter N: ";
            cin >> n;
            vector<Song> results = heap.getTopN(n);
            cout << "\nTop " << n << " Songs (Max Heap):\n";
            printSongs(results);
            cout << "Query Time: " << heap.queryTime << " ms\n";

        } else if (choice == 3) {
            if (!loaded) { cout << "Please load the dataset first!\n"; continue; }
            int n;
            cout << "Enter N: ";
            cin >> n;
            vector<Song> results = tree.getTopN(n);
            cout << "\nTop " << n << " Songs (Splay Tree):\n";
            printSongs(results);
            cout << "Query Time: " << tree.queryTime << " ms\n";

        } else if (choice == 4) {
            if (!loaded) { cout << "Please load the dataset first!\n"; continue; }
            int n;
            cout << "Enter N: ";
            cin >> n;

            vector<Song> heapResults = heap.getTopN(n);
            vector<Song> treeResults = tree.getTopN(n);

            cout << "\n--- Max Heap Results ---\n";
            printSongs(heapResults);
            cout << "Build Time: " << heap.buildTime << " ms\n";
            cout << "Query Time: " << heap.queryTime << " ms\n";

            cout << "\n--- Splay Tree Results ---\n";
            printSongs(treeResults);
            cout << "Build Time: " << tree.buildTime << " ms\n";
            cout << "Query Time: " << tree.queryTime << " ms\n";

        } else if (choice == 5) {
            cout << "Bye!\n";
            break;

        } else {
            cout << "Invalid choice, try again.\n";
        }
    }

    return 0;
}