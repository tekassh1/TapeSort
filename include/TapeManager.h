#ifndef TAPEMANAGER_H
#define TAPEMANAGER_H

#include <string>
#include "ITapeManager.h"

#define TMP_DIR_NAME "tmp"

class TapeManager : public ITapeManager {
   private:
    std::string input_tape_name;
    FILE* input_tape_file;
    size_t tape_len;
    size_t ram_byes;

    size_t tmp_tapes_amount;
    FILE** tmp_tapes;

    size_t elems_in_one_tape;

    void clearTmpDir(std::string dir_name) override;
    void createTmpDir() override;
    void createTmpTapes() override;

   public:
    TapeManager(std::string input_tape_name, size_t tape_len, size_t ram_byes);

    ~TapeManager();
};

#endif  // TAPEMANAGER_H
