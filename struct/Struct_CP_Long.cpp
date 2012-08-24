#include "Struct_CP_Long.h"

#include "ConstantPoolInfo_Long.h"

Struct_CP_Long::Struct_CP_Long(const ConstantPoolInfo_Long &v)
    : value(v.value())
{
}

void Struct_CP_Long::writeThis(DataWriter &data) const
{
}
