#pragma once
#include <vector>
#include <chrono>
#include "Song.h"

// max heap keeps the most popular song at the top
class MaxHeap {
private:
    std::vector<Song> heap;

    // these help us navigate the array like a tree
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void heapifyUp(int i);
    void heapifyDown(int i);

public:
    double buildTime = 0;
    double queryTime = 0;

    void insert(const Song& song);
    void buildHeap(const std::vector<Song>& songs);
    std::vector<Song> getTopN(int n);
    int size() { return heap.size(); }
};