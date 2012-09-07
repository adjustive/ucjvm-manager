#ifndef STRUCT_CP_DOUBLE_H
#define STRUCT_CP_DOUBLE_H

#include "Struct_CP.h"
class ConstantPoolInfo_Double;

class Struct_CP_Double : public Struct_CP
{
public:
    Struct_CP_Double(ConstantPoolInfo_Double const &v);

    void resolveClassReferences(const ResolveContext &context);

    void writeConstantData(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    Type type() const { return CONSTANT_TYPE_DOUBLE; }

    char const *typeName() const { return "CP_Double"; }

private:
    double value;
};

#endif // STRUCT_CP_DOUBLE_H
