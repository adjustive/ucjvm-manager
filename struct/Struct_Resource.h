#ifndef STRUCT_RESOURCE_H
#define STRUCT_RESOURCE_H

#include "Struct_ResourceName.h"

#include <QByteArray>

class Struct_Resource : public Struct
{
public:
    Struct_Resource(QString name);

    MemoryModel::Align alignment() const { return MemoryModel::INT16_ALIGN; }
    void writeStruct(DataWriter &data) const;
    void writeData(DataWriter &data) const;
    quint32 computeMemoryMap(MemoryModel const &memoryModel, quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

protected:
    Struct_ResourceName name;
    QByteArray data;
};

#endif // STRUCT_RESOURCE_H
