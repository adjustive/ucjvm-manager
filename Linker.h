#ifndef LINKER_H
#define LINKER_H

#include "JVMConfig.h"
#include "JVMClassList.h"

struct LinkerPrivate;

class Linker
{
public:
    Linker(JVMConfig config, JVMClassList classList, QStringList resourceFiles);
    ~Linker();

    void link();

private:
    Q_DECLARE_PRIVATE(Linker)
    QScopedPointer<LinkerPrivate> d_ptr;
};

#endif // LINKER_H
