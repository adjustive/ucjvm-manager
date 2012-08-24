#include "Struct_CP_String.h"

#include "ConstantPoolInfo_String.h"

Struct_CP_String::Struct_CP_String(ConstantPoolInfo_String const &v)
    : stringIndex(v.nameIndex())
{
}

void Struct_CP_String::writeThis(DataWriter &data) const
{
}
