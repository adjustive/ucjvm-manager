#include "Linker.h"

#include "Struct_ClassTable.h"

#include <QTextStream>
#include <QDebug>

#include <cstdio>

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

    QString map;
    QTextStream ts(&map);
    classTable.printMemoryMap(ts);
    ts.flush();
    fprintf(stderr, "%s", map.toUtf8().constData());

    qDebug("linking done");
}
