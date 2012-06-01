#ifndef APROLOGGER_H
#define APROLOGGER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

namespace APro
{
    class AProLogger
    {
        public :
        //Constructeur
        AProLogger();

        //Destructeur
        virtual ~AProLogger();

        template<class T> AProLogger& operator <<( const T& message);

        virtual void writeMSG(const std::string& message) = 0;
    };

    template<class T> AProLogger& AProLogger::operator <<(const T& message)
    {
        std::ostringstream Stream;
        Stream << message;
        writeMSG(Stream.str());

        return *this;
    }
}
#endif
