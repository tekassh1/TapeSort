#ifndef TAPEINTERFACE_H
#define TAPEINTERFACE_H

#include <string>

class ITapeManager {
   protected:
    virtual void clearTmpDir(std::string dir_name) = 0;
    virtual void createTmpDir() = 0;
    virtual void createTmpTapes() = 0;
    virtual void prepareTapes() = 0;
    virtual void closeTmp() = 0;
    virtual int getTempTapesAmount() = 0;
};

#endif  // TAPEINTERFACE_H
