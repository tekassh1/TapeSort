#ifndef MINHEAP_H
#define MINHEAP_H

#include <cstdint>
#include <cstddef>

struct HeapNode {
    int32_t number;
    size_t file_idx;
};

class MinHeap {
private:
    HeapNode* heap;
    size_t heap_size;
    size_t capacity;

    void heapify(size_t i);

public:
    MinHeap(size_t heap_size);

    void insert(HeapNode node);
    HeapNode extractMin();
    HeapNode getMin();

    ~MinHeap();
};

// class MinHeap {
//
//     HeapNode* heap;
//     int heap_size;
//
//     int left(size_t i);
//     int right(size_t i);
//     void swap(HeapNode* x, HeapNode* y);
//     void replaceMin(HeapNode x);
//     void MinHeapify(size_t);
//
// public:
//
//     MinHeap(size_t size);
//     HeapNode getMin();
//
//     ~MinHeap();
// };

#endif //MINHEAP_H
