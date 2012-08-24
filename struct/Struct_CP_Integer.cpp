#include "Struct_CP_Integer.h"

#include "ConstantPoolInfo_Integer.h"

Struct_CP_Integer::Struct_CP_Integer(const ConstantPoolInfo_Integer &v)
    : value(v.value())
{
}

void Struct_CP_Integer::writeThis(DataWriter &data) const
{
}
