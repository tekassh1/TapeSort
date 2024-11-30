#include "Sorter.h"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

Sorter::Sorter(std::string temp_dir_name, size_t ram_bytes)
    : heap(ram_bytes / sizeof(HeapNode)),
      temp_dir_name(temp_dir_name) {
    this->ram_bytes = ram_bytes;
}

void Sorter::closeTmp() {
    for (auto& tape : tmp_tapes) {
        tape.close();
    }
}

void Sorter::prepareTapes() {
    for (const auto& entry : fs::directory_iterator(temp_dir_name)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            std::ifstream tmp_tape(filename);

            if (!tmp_tape.is_open()) {
                std::cerr << "Temp tape error!" << std::endl;
                closeTmp();
                exit(1);
            }

            tmp_tapes.push_back(std::move(tmp_tape));
        }
    }
}

bool Sorter::checkEnoughRam() {
    if (tmp_tapes.size() * sizeof(HeapNode) > ram_bytes) {
        std::cerr << "Too low memory! Sorting is impossible." << std::endl;
        return false;
    }
    return true;
}

void Sorter::sortTapes(std::string out_filename) {
    prepareTapes();

    if (!checkEnoughRam())
        return;

    std::ofstream out(out_filename);
    if (!out.is_open()) {
        std::cerr << "Error opening output file!" << std::endl;
        closeTmp();
        exit(1);  // TODO очистить кучу
    }

    for (size_t i = 0; i < tmp_tapes.size(); i++) {
        int32_t num;
        tmp_tapes[i] >> num;
        heap.insert(HeapNode{.file_idx = i, .number = num});
    }

    bool read = false;

    while (true) {
        HeapNode min = heap.getMin(); // TODO проверить, если куча пустая (тогда все числа в файлах закончились)
        out << min.number << std::endl;

        heap.extractMin();

        int32_t num;
        if (tmp_tapes[min.file_idx] >> num) {
            read = true;
            heap.insert(HeapNode{.file_idx = min.file_idx, .number = num});
        }

        if (!read) {
            continue;
            break; // TODO точно ???
        }
    }
}