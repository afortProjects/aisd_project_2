#pragma once
#include "my_vector.h"
#include "structs.h"

class myPriorityQueue {
public:
    myVector<Pair<int, int>> heap;

    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }
    int parent(int i) { return (i - 1) / 2; }
    void sift_up(int i);
    void sift_down(int i);

public:
    myPriorityQueue();

    void push(Pair<int, int> n);
    void pop();
    Pair<int, int>& top() { return this->heap[0]; }
    bool empty() { return this->heap.getSize() == 0; }

};

