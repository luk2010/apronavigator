#ifndef APROFILELOGGER_H
#define APROFILELOGGER_H

#include "AProLogger.h"

namespace APro
{
    class AProFileLogger : public AProLogger
    {
        public :
        //Constructeur
        AProFileLogger(const std::string& fileToLog = "OutLog.log");

        //Destructeur
        ~AProFileLogger();

        static void reportError(const std::string& message,const std::string& fileName = "Error.log");

        private :
        virtual void writeMSG(const std::string& message);

        std::ofstream FileforLogger;
    };
}
#endif
