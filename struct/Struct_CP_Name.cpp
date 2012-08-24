#include "Struct_CP_Name.h"

#include "ConstantPoolInfo_NameAndType.h"

Struct_CP_Name::Struct_CP_Name(const ConstantPoolInfo_NameAndType &v)
    : nameIndex(v.nameIndex())
    , descriptorIndex(v.descriptorIndex())
{
}

void Struct_CP_Name::writeThis(DataWriter &data) const
{
}
