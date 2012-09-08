#ifndef STRUCT_RESOURCETABLE_H
#define STRUCT_RESOURCETABLE_H

#include "Struct_Resource.h"
#include "ResourceEditor.h"

#include <QSharedPointer>
#include <QStringList>

class Struct_ResourceTable : public Struct
{
public:
    Struct_ResourceTable(QStringList resourceFiles, const ResourceEditor::Collection &editors);

    quint8 alignment() const { return 4; }
    void writeStruct(DataWriter &data) const;
    void writeData(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    char const *typeName() const { return "ResourceTable"; }

private:
    QList<QSharedPointer<Struct_Resource> > resources;
};

#endif // STRUCT_RESOURCETABLE_H
