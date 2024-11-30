#include "MinHeap.h"

MinHeap::MinHeap(HeapNode a[], int size) {
    heap_size = size;
    heap = a;
    int i = (heap_size - 1) / 2;
    while (i >= 0) {
        MinHeapify(i);
        i--;
    }
}

void MinHeap::MinHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;

    if (l < heap_size && heap[l].number < heap[i].number)
        smallest = l;

    if (r < heap_size && heap[r].number < heap[smallest].number)
        smallest = r;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        MinHeapify(smallest);
    }
}

int MinHeap::left(int i) {
    return 2 * i + 1;
}

int MinHeap::right(int i) {
    return 2 * i + 2;
}

HeapNode MinHeap::getMin() {
    return heap[0];
}

void MinHeap::replaceMin(HeapNode x) {
    heap[0] = x;
    MinHeapify(0);
}

void MinHeap::swap(HeapNode* x, HeapNode* y) {
    HeapNode temp = *x;
    *x = *y;
    *y = temp;
}