#ifndef STRUCT_CP_TABLE_H
#define STRUCT_CP_TABLE_H

#include "Struct.h"
#include "Struct_CP.h"
class ConstantPool;

#include <QSharedPointer>

class Struct_CP_Table : public Struct
{
public:
    Struct_CP_Table(ConstantPool const &constantPool);

    void writeStruct(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

private:
    QList<QSharedPointer<Struct_CP> > constants;
};

#endif // STRUCT_CP_TABLE_H
