#ifndef STRUCT_CP_FIELD_H
#define STRUCT_CP_FIELD_H

#include "Struct_CP.h"
class Struct_Field;
class Struct_Class;
class ConstantPoolInfo_Fieldref;

class Struct_CP_Field : public Struct_CP
{
public:
    Struct_CP_Field(ConstantPoolInfo_Fieldref const &v);

    void resolveClassReferences(const ResolveContext &context);
    void resolveFieldReferences(const ResolveContext &context);

    void writeStruct(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    Type type() const { return CONSTANT_TYPE_FIELD_REF; }

    char const *typeName() const { return "CP_Field"; }

private:
    quint16 classIndex;
    quint16 descriptorIndex;
    Struct_Field const *fieldAddress;
    Struct_Class const *classAddress;
};

#endif // STRUCT_CP_FIELD_H
