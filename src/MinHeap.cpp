#include "MinHeap.h"

MinHeap::MinHeap(HeapNode a[], int size) {
    heap_size = size;
    harr = a;
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

    if (l < heap_size && harr[l].number < harr[i].number) smallest = l;

    if (r < heap_size && harr[r].number < harr[smallest].number) smallest = r;

    if (smallest != i) {
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}

int MinHeap::left(int i) {
    return (2 * i + 1);
}

int MinHeap::right(int i) {
    return (2 * i + 2);
}

HeapNode MinHeap::getMin() {
    return harr[0];
}

void MinHeap::replaceMin(HeapNode x)
{
    harr[0] = x;
    MinHeapify(0);
}