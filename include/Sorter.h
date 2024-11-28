#ifndef SORTER_H
#define SORTER_H

#include <cstdint>

struct HeapNode {
    int number;
    int file_idx;
};

class Sorter {
    priority_queue <int32_t, , greater<int>> pq;
    public:

}

#endif //SORTER_H
