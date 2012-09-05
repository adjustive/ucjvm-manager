#include "Linker.h"

#include "Struct_ClassTable.h"
#include "MemoryWriter.h"
#include "DryRunWriter.h"
#include "MemoryMapWriter.h"

#include <QTextStream>
#include <QDebug>

#include <sys/time.h>
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

    timeval start;
    gettimeofday(&start, NULL);

    quint32 const baseAddress = d->config.baseAddress();

    Struct_ClassTable classTable(d->classList, baseAddress, d->config.nativeInterface());

#if 0
    DryRunWriter drw;
    classTable.write(drw);
    qFatal("%u", drw.memorySize());
#endif

    {
        QFile out("memory.log");
        out.open(QFile::WriteOnly);

        QString map;
        QTextStream ts(&out);
        classTable.printMemoryMap(ts);
    }

    {
        MemoryMapWriter memMap(baseAddress);
        classTable.write(memMap);
        memMap.flush();

        QFile out("new.xml");
        out.open(QFile::WriteOnly);
        out.write(memMap.data());
    }

    {
        MemoryWriter writer(baseAddress);
        classTable.write(writer);

        QFile out("new.bin");
        out.open(QFile::WriteOnly);
        out.write(writer.data());

        timeval end;
        gettimeofday(&end, NULL);

        timeval diff;
        timersub(&end, &start, &diff);

        qDebug("linking done: %d bytes %ld.%06lu secs", writer.size(), diff.tv_sec, diff.tv_usec);
    }
}
