#ifndef STRUCT_CP_NAME_H
#define STRUCT_CP_NAME_H

#include "Struct_CP.h"
class ConstantPoolInfo_NameAndType;

class Struct_CP_Name : public Struct_CP
{
public:
    Struct_CP_Name(ConstantPoolInfo_NameAndType const &v);

    void writeThis(DataWriter &data) const;

    Type type() const { return CONSTANT_TYPE_NAME_AND_TYPE; }

public:
    quint16 nameIndex;
    quint16 descriptorIndex;
};

#endif // STRUCT_CP_NAME_H
