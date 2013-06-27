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
    Config config;
    ClassList classList;
    QStringList resourceFiles;
    ResourceEditor::Collection const &editors;

    LinkerPrivate(Config config, ClassList classList, QStringList resourceFiles, ResourceEditor::Collection const &editors)
        : config(config)
        , classList(classList)
        , resourceFiles(resourceFiles)
        , editors(editors)
    {
    }
};

Linker::Linker(Config config, ClassList classList, QStringList resourceFiles, const ResourceEditor::Collection &editors)
    : d_ptr(new LinkerPrivate(config, classList, resourceFiles, editors))
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
    MemoryModel const &memoryModel = d->config.memoryModel();

    Struct_ClassTable classTable(d->classList,
                                 baseAddress,
                                 d->config.nativeInterface(),
                                 d->resourceFiles,
                                 d->editors,
                                 memoryModel);

    if (0)
    {
        QFile out("memory.log");
        out.open(QFile::WriteOnly);

        QString map;
        QTextStream ts(&out);
        classTable.printMemoryMap(ts);
    }

    if (0)
    {
        MemoryMapWriter memMap(memoryModel, baseAddress);
        classTable.write(memMap);
        memMap.flush();

        QFile out("new.xml");
        out.open(QFile::WriteOnly);
        out.write(memMap.data());
    }

    {
        MemoryWriter writer(memoryModel, baseAddress);
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

    {
        QFile out("new.ld");
        out.open(QFile::WriteOnly);

        QTextStream ts(&out);
        ts << "0x" << hex << baseAddress;
    }
}
