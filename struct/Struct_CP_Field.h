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

    void writeThis(DataWriter &data) const;

    Type type() const { return CONSTANT_TYPE_FIELD_REF; }

public:
    quint16 classIndex;
    quint16 descriptorIndex;
    Struct_Field *fieldAddress;
    Struct_Class *classAddress;
};

#endif // STRUCT_CP_FIELD_H
