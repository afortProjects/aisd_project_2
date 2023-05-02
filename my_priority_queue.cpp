#include "my_priority_queue.h"
void myPriorityQueue::sift_up(int i)
{
    //First value is cost second value is index in vector
    while (i > 0 && heap[parent(i)].firstValue > heap[i].firstValue) {
        Pair<int, int> temp = heap[i];
        heap[i] = heap[parent(i)];
        heap[parent(i)] = temp;
        i = parent(i);
    }
}

void myPriorityQueue::sift_down(int i)
{
    int min_index = i;
    int l = left(i);
    int r = right(i);
    if (l < heap.getSize() && heap[l].firstValue < heap[min_index].firstValue) {
        min_index = l;
    }
    if (r < heap.getSize() && heap[r].firstValue < heap[min_index].firstValue) {
        min_index = r;
    }
    if (i != min_index) {
        Pair<int, int> temp = heap[i];
        heap[i] = heap[min_index];
        heap[min_index] = temp;
        sift_down(min_index);
    }
}

void myPriorityQueue::push(Pair<int, int> n)
{
    heap.push_back(n);
    sift_up(heap.getSize() - 1);
}

void myPriorityQueue::pop()
{
    heap[0] = heap.back();
    heap.pop_back();
    sift_down(0);
}