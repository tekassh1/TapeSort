#ifndef SORTER_H
#define SORTER_H

#include <cstdint>
#include <fstream>
#include <vector>

#include "MinHeap.h"

class Sorter {

private:
	size_t ram_bytes;

	std::string temp_dir_name;
	MinHeap heap;
	std::vector<std::ifstream> tmp_tapes;
	void closeTmp();

	void prepareTapes();
	bool checkEnoughRam();

public:
	Sorter(std::string temp_dir_name, size_t heap_size);
	void sortTapes(std::string out_filename);
};

#endif //SORTER_H
