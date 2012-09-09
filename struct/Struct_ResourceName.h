#ifndef STRUCT_RESOURCENAME_H
#define STRUCT_RESOURCENAME_H

#include "Struct.h"

class Struct_ResourceName : public Struct
{
public:
    Struct_ResourceName(QString name);

    MemoryModel::Align alignment() const { return MemoryModel::INT8_ALIGN; }
    void writeStruct(DataWriter &data) const;
    quint32 computeMemoryMap(MemoryModel const &memoryModel, quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    char const *typeName() const { return "ResourceName"; }

private:
    QString name;
};

#endif // STRUCT_RESOURCENAME_H
