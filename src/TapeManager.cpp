#include "TapeManager.h"

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

TapeManager::TapeManager(std::string input_tape_name, size_t ram_bytes) {
    this->input_tape_name = input_tape_name;
    this->ram_bytes = ram_bytes;

    createTmpTapes();
}

void TapeManager::clearTmpDir(std::string dir_name) {
    try {
        if (fs::exists(dir_name) && fs::is_directory(dir_name)) {
            for (const auto& entry : fs::directory_iterator(dir_name)) {
                const auto& path = entry.path();

                if (fs::is_directory(path))
                    clearTmpDir(path);

                fs::remove(path);
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::ostringstream oss;
        oss << "Error while clearing temp directory: " << TMP_DIR_NAME << ".";
        std::cerr << oss.str() << std::endl;
        exit(1);
    }
}

void TapeManager::createTmpDir() {
    clearTmpDir(TMP_DIR_NAME);

    std::filesystem::path dir = TMP_DIR_NAME;

    if (!std::filesystem::exists(dir)) {
        if (!std::filesystem::create_directory(dir)) {
            std::ostringstream oss;
            oss << "Failed to create directory \'" << TMP_DIR_NAME << "\'.";
            std::cerr << oss.str() << std::endl;
            exit(1);
        }
    } else {
        clearTmpDir(TMP_DIR_NAME);
    }
}

void TapeManager::writeChunk(int32_t chunk[], size_t chunk_size, int32_t elems_in_chunk, size_t tape_number) {
    std::sort(chunk, chunk + elems_in_chunk);
    std::ofstream tmp_tape(fs::path(TMP_DIR_NAME) / ("tape_" + std::to_string(tape_number)));

    if (!tmp_tape.is_open()) {
        std::cerr << "Temp tape error!" << std::endl;
        exit(1);
    }

    for (size_t j = 0; j < elems_in_chunk; j++) {
        tmp_tape << chunk[j] << " ";
    }
    tmp_tape.close();
}

void TapeManager::createTmpTapes() {
    std::ifstream input_tape_file(input_tape_name);
    if (!input_tape_file.is_open()) {
        std::cerr << "Input tape error!" << std::endl;
        exit(1);
    }

    createTmpDir();

    int32_t number;
    int32_t chunck_size = ram_bytes / sizeof(int32_t);

    size_t idx = 0;
    int32_t chunk[chunck_size];
    int32_t elems_in_chunk = 0;
    int32_t tmp_tapes_count = 0;

    while (input_tape_file >> number) {
        if (idx >= chunck_size) {
            writeChunk(chunk, chunck_size, elems_in_chunk, tmp_tapes_count);

            idx = 0;
            elems_in_chunk = 0;
            tmp_tapes_count++;
        }
        chunk[idx] = number;
        elems_in_chunk++;
        idx++;
    }
    writeChunk(chunk, chunck_size, elems_in_chunk, tmp_tapes_count);
    input_tape_file.close();
}

TapeManager::~TapeManager() {
    clearTmpDir(TMP_DIR_NAME);
}
