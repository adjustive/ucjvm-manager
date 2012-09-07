#ifndef STRUCT_CP_LONG_H
#define STRUCT_CP_LONG_H

#include "Struct_CP.h"
class ConstantPoolInfo_Long;

class Struct_CP_Long : public Struct_CP
{
public:
    Struct_CP_Long(ConstantPoolInfo_Long const &v);

    void resolveClassReferences(const ResolveContext &context);

    void writeConstantData(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    Type type() const { return CONSTANT_TYPE_LONG; }

    char const *typeName() const { return "CP_Long"; }

private:
    quint64 value;
};

#endif // STRUCT_CP_LONG_H
