#pragma once
#include <vector>
#include <chrono>
#include "Song.h"

// splay tree moves recently accessed nodes to the top
class SplayTree {
private:
    struct Node {
        Song song;
        Node* left;
        Node* right;

        Node(Song s) {
            song = s;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    Node* splay(Node* root, int popularity);
    void getTopNHelper(Node* node, std::vector<Song>& result, int n);
    void deleteTree(Node* node);

public:
    double buildTime = 0;
    double queryTime = 0;

    SplayTree() { root = nullptr; }
    ~SplayTree() { deleteTree(root); }

    void insert(const Song& song);
    void buildTree(const std::vector<Song>& songs);
    std::vector<Song> getTopN(int n);
};