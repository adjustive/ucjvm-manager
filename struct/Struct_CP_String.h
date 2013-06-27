#ifndef STRUCT_CP_STRING_H
#define STRUCT_CP_STRING_H

#include "Struct_CP.h"
class ConstantPoolInfo_String;

class Struct_CP_String : public Struct_CP
{
public:
    Struct_CP_String(ConstantPoolInfo_String const &v);

    void resolveClassReferences(const ResolveContext &context);

    void writeConstantData(DataWriter &data) const;
    quint32 computeMemoryMap(MemoryModel const &memoryModel, quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    Type type() const { return CONSTANT_TYPE_STRING; }

    char const *typeName() const { return "CP_String"; }

private:
    quint16 stringIndex;
};

#endif // STRUCT_CP_STRING_H
