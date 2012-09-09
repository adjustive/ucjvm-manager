#ifndef STRUCT_EXCEPTIONS_H
#define STRUCT_EXCEPTIONS_H

#include "Struct.h"

#include <QList>

class Struct_Exceptions : public Struct
{
public:
    Struct_Exceptions();

    MemoryModel::Align alignment() const { return MemoryModel::INT16_ALIGN; }
    void writeStruct(DataWriter &data) const;
    quint32 computeMemoryMap(MemoryModel const &memoryModel, quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    char const *typeName() const { return "Exceptions"; }

    void add(QList<quint16> exceptions);
    quint16 size() const;

private:
    QList<quint16> exceptions; // index into constant pool
};

#endif // STRUCT_EXCEPTIONS_H
