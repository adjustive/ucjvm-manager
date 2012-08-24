#include "Struct_CP_Double.h"

#include "ConstantPoolInfo_Double.h"

Struct_CP_Double::Struct_CP_Double(ConstantPoolInfo_Double const &v)
    : value(v.value())
{
}

void Struct_CP_Double::writeThis(DataWriter &data) const
{
}
