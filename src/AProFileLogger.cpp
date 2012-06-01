#include "AProFileLogger.h"
#include <iostream>

namespace APro
{
    AProFileLogger::AProFileLogger(const std::string& fileToLog)
    : FileforLogger(fileToLog.c_str())
    {
        FileforLogger << "                                             ----------------------------------------" << std::endl;
        FileforLogger << "                                             -----------APro logger Engine-----------" << std::endl;
        FileforLogger << "                                             ----------------------------------------" << std::endl;
    }

    AProFileLogger::~AProFileLogger()
    {
        FileforLogger << std::endl;
        FileforLogger << "                                             ========================================" << std::endl;
        FileforLogger << "                                             ========================================" << std::endl;
    }

    void AProFileLogger::writeMSG(const std::string& message)
    {
        FileforLogger << message << std::endl;
    }

    void AProFileLogger::reportError(const std::string& message, const std::string& fileName)
    {
        std::ofstream File(fileName.c_str(),std::ios::out | std::ios::app);
        File << message << std::endl;
        File.close();
    }
}
