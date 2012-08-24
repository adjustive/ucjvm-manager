#include "Struct_CP_Float.h"

#include "ConstantPoolInfo_Float.h"

Struct_CP_Float::Struct_CP_Float(const ConstantPoolInfo_Float &v)
    : value(v.value())
{
}

void Struct_CP_Float::writeThis(DataWriter &data) const
{
}
