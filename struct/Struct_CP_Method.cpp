#include "Struct_CP_Method.h"

#include "ConstantPoolInfo_Methodref.h"

Struct_CP_Method::Struct_CP_Method(const ConstantPoolInfo_Methodref &v)
    : classIndex(v.nameIndex())
    , descriptorIndex(v.descriptorIndex())
    , address(0)
    , realClass(0)
{
}

void Struct_CP_Method::writeThis(DataWriter &data) const
{
}
