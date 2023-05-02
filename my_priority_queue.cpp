#include "my_priority_queue.h"
void myPriorityQueue::sift_up(int i)
{
    while (i > 0 && heap[parent(i)].cost < heap[i].cost) {
        City temp = heap[i];
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
    if (l < heap.getSize() && heap[l].cost > heap[min_index].cost) {
        min_index = l;
    }
    if (r < heap.getSize() && heap[r].cost > heap[min_index].cost) {
        min_index = r;
    }
    if (i != min_index) {
        City temp = heap[i];
        heap[i] = heap[min_index];
        heap[min_index] = temp;
        sift_down(min_index);
    }
}

void myPriorityQueue::push(City n)
{
    heap.push_back(n);
    sift_up(heap.getSize() - 1);
}

void myPriorityQueue::pop()
{
    heap.front() = heap.back();
    heap.pop_back();
    sift_down(0);
}