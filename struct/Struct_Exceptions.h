#ifndef STRUCT_EXCEPTIONS_H
#define STRUCT_EXCEPTIONS_H

#include "Struct.h"

#include <QList>

class Struct_Exceptions : public Struct
{
public:
    Struct_Exceptions();

    void writeStruct(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    void add(QList<quint16> exceptions);
    quint16 size() const;

private:
    QList<quint16> exceptions; // index into constant pool
};

#endif // STRUCT_EXCEPTIONS_H
