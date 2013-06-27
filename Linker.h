#ifndef LINKER_H
#define LINKER_H

#include "Config.h"
#include "ClassList.h"
#include "ResourceEditor.h"

struct LinkerPrivate;

class Linker
{
public:
    Linker(Config config, ClassList classList, QStringList resourceFiles, ResourceEditor::Collection const &editors);
    ~Linker();

    void link();

private:
    Q_DECLARE_PRIVATE(Linker)
    QScopedPointer<LinkerPrivate> d_ptr;
};

#endif // LINKER_H
