#include <iostream>

#include "Sorter.h"
#include "TapeManager.h"

int main() {
    size_t ram_bytes = 20000;

    Sorter sorter("InputTape", "Out", ram_bytes);
    sorter.sortTapes();

    return 0;
}