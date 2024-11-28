#include "TapeManager.h"

#include <cmath>
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

TapeManager::TapeManager(std::string input_tape_name, size_t tape_len, size_t ram_bytes) {
    this->input_tape_name = input_tape_name;
    this->tape_len = tape_len;
    this->ram_byes = ram_byes;

    input_tape_file = fopen(input_tape_name.c_str(), "rb");
    if (!input_tape_file) {
        std::cerr << "Tape error!" << std::endl;
        exit(1);
    }

    tmp_tapes_amount = std::floor(tape_len * sizeof(int32_t) / ram_bytes);
    elems_in_one_tape = tape_len / tmp_tapes_amount;

    tmp_tapes = new FILE*[tmp_tapes_amount];
}

void TapeManager::clearTmpDir(std::string dir_name) {
    try {
        if (fs::exists(dir_name) && fs::is_directory(dir_name)) {
            for (const auto& entry : fs::directory_iterator(dir_name)) {
                const auto& path = entry.path();

                if (fs::is_directory(path)) {
                    clearTmpDir(path);
                    fs::remove(path);
                } else {
                    fs::remove(path);
                }
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
    std::filesystem::path dir = TMP_DIR_NAME;

    if (!std::filesystem::exists(dir)) {
        if (!std::filesystem::create_directory(dir)) {
            std::ostringstream oss;
            oss << "Failed to create directory " << TMP_DIR_NAME << ".";
            std::cerr << oss.str() << std::endl;
            exit(1);
        }
    } else {
        clearTmpDir(TMP_DIR_NAME);
    }
}

void TapeManager::createTmpTapes() {
    createTmpDir();

    for (size_t i = 0; i < tmp_tapes_amount; i++) {
        tmp_tapes[i] = fopen((TMP_DIR_NAME + std::to_string(i)).c_str(), "wb");
        if (!tmp_tapes[i]) {
            std::cerr << "Temp tape error!" << std::endl;
            exit(1);
        }

        int32_t chunk[elems_in_one_tape];
        for (size_t j = 0; j < elems_in_one_tape; j++) {
            int32_t num;
            if (!fread(&num, sizeof(num), 1, input_tape_file)) {
                if (!feof(input_tape_file)) {
                    std::cerr << "Input tape reading error!" << std::endl;
                    exit(1);
                }
            }
            chunk[j] = num;
        }

        if (!fwrite(chunk, sizeof(int32_t), elems_in_one_tape, tmp_tapes[i])) {
            std::cerr << "Temp tape writing error!" << std::endl;
            exit(1);
        }

        fclose(tmp_tapes[i]);
    }
}

TapeManager::~TapeManager() {
    for (size_t i = 0; i < tmp_tapes_amount; i++) {
        fclose(tmp_tapes[i]);
    }
    delete[] tmp_tapes;
    fclose(input_tape_file);
}
