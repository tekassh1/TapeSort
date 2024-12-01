#include "TapeManager.h"

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

namespace fs = std::filesystem;

TapeManager::TapeManager(std::string input_tape_name, size_t ram_bytes) {
    this->input_tape_name = input_tape_name;
    this->ram_bytes = ram_bytes;

    parseConfig();
    createTmpTapes();
}

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::istringstream stream(str);
    std::string token;

    while (std::getline(stream, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

int TapeManager::read_delay = -1;
int TapeManager::write_delay = -1;
int TapeManager::move_delay = -1;

void TapeManager::parseConfig() {
    std::ifstream config_file(CONFIG_FILE_NAME);
    if (!config_file.is_open()) {
        std::ostringstream oss;
        oss << "Error reading config file: \'" << CONFIG_FILE_NAME << "\'.";
        std::cerr << oss.str() << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(config_file, line)) {
        std::vector<std::string> tokens = split(line, ':');

        if (tokens[0] == "read_delay")
            read_delay = std::stoi(tokens[1]);
        if (tokens[0] == "write_delay")
            write_delay = std::stoi(tokens[1]);
        if (tokens[0] == "move_delay")
            move_delay = std::stoi(tokens[1]);
    }
    if (read_delay < 0 || write_delay < 0 || move_delay < 0) {
        std::ostringstream oss;
        oss << "Wrong config file: \'" << CONFIG_FILE_NAME
            << "\'\nYou should pass `read_delay`, `write_delay` and `move_delay`"
               " parameters in config file. \nSyntax: <parameter>:<value> (in nanoseconds, new line for each param).";
        std::cerr << oss.str() << std::endl;
        exit(1);
    }
}

int TapeManager::getReadDelay() {
    return read_delay;
}

int TapeManager::getWriteDelay() {
    return write_delay;
}

int TapeManager::getMoveDelay() {
    return move_delay;
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
        tmp_tape << chunk[j] << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::nanoseconds(getMoveDelay() * (elems_in_chunk - 1))); // emulate tape delays
    std::this_thread::sleep_for(std::chrono::nanoseconds(getWriteDelay() * elems_in_chunk));

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
        std::this_thread::sleep_for(std::chrono::nanoseconds(getMoveDelay())); // emulate tape delays
        std::this_thread::sleep_for(std::chrono::nanoseconds(getReadDelay()));

        chunk[idx] = number;
        elems_in_chunk++;
        idx++;

        if (idx >= chunck_size) {
            writeChunk(chunk, chunck_size, elems_in_chunk, tmp_tapes_count);

            idx = 0;
            elems_in_chunk = 0;
            tmp_tapes_count++;
        }
    }
    if (elems_in_chunk)
        writeChunk(chunk, chunck_size, elems_in_chunk, tmp_tapes_count);
    input_tape_file.close();
}

TapeManager::~TapeManager() {
    clearTmpDir(TMP_DIR_NAME);
}
