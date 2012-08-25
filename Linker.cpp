#include "Linker.h"

#include "Struct_ClassTable.h"
#include "MemoryWriter.h"

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

    Struct_ClassTable classTable(d->classList, d->config.baseAddress(), d->config.nativeInterface());

    QString map;
    QTextStream ts(&map);
    classTable.printMemoryMap(ts);
//    fprintf(stderr, "%s", map.toUtf8().constData());

    MemoryWriter writer;
    classTable.write(writer);

    qDebug("linking done: %d bytes", writer.size());
}
