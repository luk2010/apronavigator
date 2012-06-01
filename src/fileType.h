#ifndef FILETYPE_H
#define FILETYPE_H

#include <QString>

namespace Type
{
    enum _type
    {
        Cpp,
        C,
        Java,
        Html,
        PHP,
        XML,
        Autres
    };

    struct FileType
    {
        bool header;
        _type type;
    };

    static bool isHeader(const QString& ext)
    {
        if(ext == "hpp" || ext == "h")
            return true;
        return false;
    }

    static FileType getFileTypeFromString(const QString& ext)
    {
        FileType ft;
        if(ext == "cpp" || ext == "hpp")
            ft.type = Cpp;
        else if (ext == "c" || ext == "h")
            ft.type = C;
        else if (ext == "jav" || ext == "java")
            ft.type = Java;
        else if (ext == "htm" || ext == "html" || ext == "xhtml" || ext == "xht")
            ft.type = Html;
        else if (ext == "php")
            ft.type = PHP;
        else if (ext == "xml")
            ft.type = XML;
        else
            ft.type = Autres;
        ft.header = isHeader(ext);
        return ft;
    }
}

using Type::FileType;

#endif // FILETYPE_H
