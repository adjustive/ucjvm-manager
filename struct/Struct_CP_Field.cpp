#include "Struct_CP_Field.h"

#include "ConstantPoolInfo_Fieldref.h"

Struct_CP_Field::Struct_CP_Field(ConstantPoolInfo_Fieldref const &v)
    : classIndex(v.nameIndex())
    , descriptorIndex(v.descriptorIndex())
    , fieldAddress(0)
    , classAddress(0)
{
}

void Struct_CP_Field::writeThis(DataWriter &data) const
{
}
