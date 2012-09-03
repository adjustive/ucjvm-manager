#ifndef STRUCT_CP_TABLE_H
#define STRUCT_CP_TABLE_H

#include "Struct.h"
#include "Struct_CP.h"
class Struct_CP_Class;
class Struct_CP_Name;
class ConstantPool;

#include <QSharedPointer>

class Struct_CP_Table : public Struct
{
public:
    Struct_CP_Table(ConstantPool const &constantPool);

    void resolveClassReferences(ResolveContext const &classTable);
    void resolveFieldReferences(const ResolveContext &context);
    void resolveMethodReferences(const ResolveContext &context);

    quint8 alignment() const { return 4; }
    void writeStruct(DataWriter &data) const;
    void writeData(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    char const *typeName() const { return "CP_Table"; }

    QString getUtf8(int index) const;
    Struct_CP_Class &getClass(int index) const;
    Struct_CP_Name const &getName(int index) const;

private:
    QList<QSharedPointer<Struct_CP> > constants;
};

#endif // STRUCT_CP_TABLE_H
