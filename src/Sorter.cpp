#include "Sorter.h"

#include <TapeManager.h>

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
            std::ifstream tmp_tape(fs::path(TMP_DIR_NAME) / filename);

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
        heap.insert(HeapNode{.number = num, .file_idx = i});
    }

    while (true) {
        std::optional<HeapNode> min = heap.extractMin();
        if (!min.has_value())
            break;

        out << min->number << std::endl;

        int32_t num;
        if (tmp_tapes[min->file_idx] >> num) {
            heap.insert(HeapNode{.number = num, .file_idx = min->file_idx});
        }
    }
}