#include "Sorter.h"
#include "TapeManager.h"

int main() {
    std::string out_dir_name = "Out";

    size_t ram_bytes = 7 * sizeof(int32_t);
    TapeManager tape_manager("InputTape", ram_bytes);
    Sorter sorter(TMP_DIR_NAME, ram_bytes);
    sorter.sortTapes(out_dir_name);
    return 0;
}