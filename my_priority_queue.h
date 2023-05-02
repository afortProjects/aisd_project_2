#pragma once
#include "my_vector.h"
#include "structs.h"
//class CompareNode {
//public:
//    bool operator()(City& n1, City& n2)
//    {
//        return n1.cost < n2.cost;
//    }
//};

class myPriorityQueue {
private:
    myVector<Pair<int, int>> heap;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }
    void sift_up(int i);
    void sift_down(int i);

public:
    myPriorityQueue() {}

    bool empty() { return heap.getSize() == 0; }
    void push(Pair<int, int> n);
    void pop();
    Pair<int, int>& top() { return heap.front(); }
};

