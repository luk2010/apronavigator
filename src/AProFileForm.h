#ifndef APROFILEFORM_H
#define APROFILEFORM_H

#include <QtGUI>
#include "fileType.h"

class AProFileForm : public QObject
{
    Q_OBJECT

public:
    AProFileForm() {}
    AProFileForm(const QString& _file, bool addToProject = false) {
        file = QFileInfo(_file);
        type = Type::getFileTypeFromString(file.suffix());
        addToCurrentProject = addToProject;
    }
    AProFileForm(const AProFileForm& other) {
        file = other.getFile();
        type = other.getType();
        addToCurrentProject = other.addToCurProject();
    }

    QFileInfo getFile() const { return file; }
    QString getName() const { return file.fileName(); }
    Type::FileType getType() const { return type; }
    bool addToCurProject() const { return addToCurrentProject; }

private:
    QFileInfo file;
    FileType type;
    bool addToCurrentProject;
};

#endif //APROFILEFORM_H
