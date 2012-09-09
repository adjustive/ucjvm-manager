#ifndef STRUCT_CP_CLASS_H
#define STRUCT_CP_CLASS_H

#include "Struct_CP.h"
class Struct_Class;
class ConstantPoolInfo_Class;

class Struct_CP_Class : public Struct_CP
{
public:
    Struct_CP_Class(const ConstantPoolInfo_Class &v);

    void resolveClassReferences(const ResolveContext &context);

    void writeConstantData(DataWriter &data) const;
    quint32 computeMemoryMap(const MemoryModel &memoryModel, quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    Type type() const { return CONSTANT_TYPE_CLASS_INFO; }

    char const *typeName() const { return "CP_Class"; }

public:
    quint16 index;
    Struct_Class const *classAddress;
};

#endif // STRUCT_CP_CLASS_H
