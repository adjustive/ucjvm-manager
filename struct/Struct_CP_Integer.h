#ifndef STRUCT_CP_INTEGER_H
#define STRUCT_CP_INTEGER_H

#include "Struct_CP.h"
class ConstantPoolInfo_Integer;

class Struct_CP_Integer : public Struct_CP
{
public:
    Struct_CP_Integer(ConstantPoolInfo_Integer const &v);

    void resolveClassReferences(const ResolveContext &context);

    void writeConstantData(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    Type type() const { return CONSTANT_TYPE_INTEGER; }

    char const *typeName() const { return "CP_Integer"; }

private:
    quint32 value;
};

#endif // STRUCT_CP_INTEGER_H
