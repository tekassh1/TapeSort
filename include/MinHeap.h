#ifndef MINHEAP_H
#define MINHEAP_H

#include <cstdint>

struct HeapNode {
    int32_t number;
    int file_idx;
};

class MinHeap {

    HeapNode* heap;
    int heap_size;

public:

    MinHeap(HeapNode a[], int size);

    int left(int i);
    int right(int i);

    HeapNode getMin();

    void MinHeapify(int);
    void replaceMin(HeapNode x);
    void swap(HeapNode* x, HeapNode* y);
};

#endif //MINHEAP_H
