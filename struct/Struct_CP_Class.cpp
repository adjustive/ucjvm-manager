#include "Struct_CP_Class.h"

#include "ConstantPoolInfo_Class.h"

Struct_CP_Class::Struct_CP_Class(const ConstantPoolInfo_Class &v)
    : index(v.nameIndex())
    , classAddress(0)
{
}

void Struct_CP_Class::writeThis(DataWriter &data) const
{
}
