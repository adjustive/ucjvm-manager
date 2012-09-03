#ifndef STRUCT_CP_DUMMY_H
#define STRUCT_CP_DUMMY_H

#include "Struct_CP.h"
class ConstantPoolInfo_Double;

#include <QSharedPointer>

class Struct_CP_Dummy : public Struct_CP
{
public:
    Struct_CP_Dummy();

    void resolveClassReferences(const ResolveContext &context);

    void writeStruct(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    Type type() const { return CONSTANT_TYPE_DUMMY; }

    char const *typeName() const { return "CP_Dummy"; }


    static QSharedPointer<Struct_CP> instance;
};

#endif // STRUCT_CP_DUMMY_H
