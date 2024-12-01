#include <iostream>

#include "Sorter.h"
#include "TapeManager.h"

// "InputTape"
// "OutTape"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Run error, required args <input filename> <out filename> <bytes amount>" << std::endl;
        return 1;
    }

    std::string input_file = argv[1];
    std::string output_file = argv[2];
    size_t bytes_amount = std::stoi(argv[3]);

    try {
        Sorter sorter(input_file, output_file, bytes_amount);
        sorter.sortTapes();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}