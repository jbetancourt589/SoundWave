#include "../include/MaxHeap.h"
#include <iostream>

using namespace std;
using namespace chrono;

// bubble up until we're in the right spot
void MaxHeap::heapifyUp(int i) {
    while (i > 0 && heap[i].popularity > heap[parent(i)].popularity) {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

// bubble down until we're in the right spot
void MaxHeap::heapifyDown(int i) {
    int largest = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if (left < (int)heap.size() && heap[left].popularity > heap[largest].popularity)
        largest = left;

    if (right < (int)heap.size() && heap[right].popularity > heap[largest].popularity)
        largest = right;

    if (largest != i) {
        swap(heap[i], heap[largest]);
        heapifyDown(largest);
    }
}

void MaxHeap::insert(const Song& song) {
    heap.push_back(song);
    heapifyUp(heap.size() - 1);
}

void MaxHeap::buildHeap(const vector<Song>& songs) {
    auto start = high_resolution_clock::now();

    for (auto& song : songs)
        insert(song);

    auto end = high_resolution_clock::now();
    buildTime = duration_cast<milliseconds>(end - start).count();
}

vector<Song> MaxHeap::getTopN(int n) {
    auto start = high_resolution_clock::now();

    // copy the heap so we dont destroy the original
    MaxHeap temp = *this;
    vector<Song> result;

    for (int i = 0; i < n && temp.size() > 0; i++) {
        result.push_back(temp.heap[0]); // top is always biggest

        // put last element at top and fix it
        temp.heap[0] = temp.heap[temp.heap.size() - 1];
        temp.heap.pop_back();
        temp.heapifyDown(0);
    }

    auto end = high_resolution_clock::now();
    queryTime = duration_cast<milliseconds>(end - start).count();

    return result;
}