#include "Linker.h"

#include "Struct_ClassTable.h"

struct LinkerPrivate
{
    JVMConfig config;
    JVMClassList classList;

    LinkerPrivate(JVMConfig config, JVMClassList classList)
        : config(config)
        , classList(classList)
    {
    }
};

Linker::Linker(JVMConfig config, JVMClassList classList)
    : d_ptr(new LinkerPrivate(config, classList))
{
}

Linker::~Linker()
{
}

void Linker::link()
{
    Q_D(Linker);
    qDebug("linking...");

    Struct_ClassTable classTable(d->classList, d->config.baseAddress());

    qDebug("linking done");
}
