#include "../include/SplayTree.h"
#include <iostream>

using namespace std;
using namespace chrono;

// rotate the node right
SplayTree::Node* SplayTree::rotateRight(Node* node) {
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    return newRoot;
}

// rotate the node left
SplayTree::Node* SplayTree::rotateLeft(Node* node) {
    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    return newRoot;
}

// brings the target node up to the root using rotations
SplayTree::Node* SplayTree::splay(Node* root, int popularity) {
    if (root == nullptr || root->song.popularity == popularity)
        return root;

    if (popularity < root->song.popularity) {
        if (root->left == nullptr) return root;

        // zig-zig
        if (popularity < root->left->song.popularity) {
            root->left->left = splay(root->left->left, popularity);
            root = rotateRight(root);
        }
        // zig-zag
        else if (popularity > root->left->song.popularity) {
            root->left->right = splay(root->left->right, popularity);
            if (root->left->right != nullptr)
                root->left = rotateLeft(root->left);
        }

        return (root->left == nullptr) ? root : rotateRight(root);
    } else {
        if (root->right == nullptr) return root;

        // zag-zig
        if (popularity < root->right->song.popularity) {
            root->right->left = splay(root->right->left, popularity);
            if (root->right->left != nullptr)
                root->right = rotateRight(root->right);
        }
        // zag-zag
        else if (popularity > root->right->song.popularity) {
            root->right->right = splay(root->right->right, popularity);
            root = rotateLeft(root);
        }

        return (root->right == nullptr) ? root : rotateLeft(root);
    }
}

void SplayTree::insert(const Song& song) {
    if (root == nullptr) {
        root = new Node(song);
        return;
    }

    root = splay(root, song.popularity);

    Node* newNode = new Node(song);

    if (song.popularity < root->song.popularity) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = nullptr;
        root = newNode;
    } else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = nullptr;
        root = newNode;
    }
}

void SplayTree::buildTree(const vector<Song>& songs) {
    auto start = high_resolution_clock::now();

    for (auto& song : songs)
        insert(song);

    auto end = high_resolution_clock::now();
    buildTime = duration_cast<milliseconds>(end - start).count();
}

// go right first since that's where the high popularity songs are
void SplayTree::getTopNHelper(Node* node, vector<Song>& result, int n) {
    if (node == nullptr || (int)result.size() >= n)
        return;

    getTopNHelper(node->right, result, n);

    if ((int)result.size() < n)
        result.push_back(node->song);

    getTopNHelper(node->left, result, n);
}

vector<Song> SplayTree::getTopN(int n) {
    auto start = high_resolution_clock::now();

    vector<Song> result;
    getTopNHelper(root, result, n);

    auto end = high_resolution_clock::now();
    queryTime = duration_cast<milliseconds>(end - start).count();

    return result;
}

void SplayTree::deleteTree(Node* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}