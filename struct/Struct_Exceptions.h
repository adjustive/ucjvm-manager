#ifndef STRUCT_EXCEPTIONS_H
#define STRUCT_EXCEPTIONS_H

#include "Struct.h"

#include <QList>

class Struct_Exceptions : public Struct
{
public:
    Struct_Exceptions();

    quint8 alignment() const { return 2; }
    void writeStruct(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    char const *typeName() const { return "Exceptions"; }

    void add(QList<quint16> exceptions);
    quint16 size() const;

private:
    QList<quint16> exceptions; // index into constant pool
};

#endif // STRUCT_EXCEPTIONS_H
