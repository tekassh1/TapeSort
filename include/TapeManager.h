#ifndef TAPEMANAGER_H
#define TAPEMANAGER_H

#include <string>
#include <vector>

#include "ITapeManager.h"

#define TMP_DIR_NAME "tmp"
#define CONFIG_FILE_NAME "config"

class TapeManager : public ITapeManager {
   private:
    std::string input_tape_name;
    size_t ram_bytes;

    void clearTmpDir(std::string dir_name) override;
    void createTmpDir() override;
    void createTmpTapes() override;
    void writeChunk(int32_t chunk[], size_t chunk_size, int32_t elems_in_chunk, size_t tape_number);

    static int read_delay;
    static int write_delay;
    static int move_delay;
    static void parseConfig();

   public:
    TapeManager(std::string input_tape_name, size_t ram_byes);

    static int getReadDelay();
    static int getWriteDelay();
    static int getMoveDelay();

    ~TapeManager();
};

#endif  // TAPEMANAGER_H
