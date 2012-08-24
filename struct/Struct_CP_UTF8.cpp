#include "Struct_CP_UTF8.h"

#include "ConstantPoolInfo_Utf8.h"

Struct_CP_UTF8::Struct_CP_UTF8(const ConstantPoolInfo_Utf8 &v)
    : data(v.string().toUtf8())
{
}

void Struct_CP_UTF8::writeThis(DataWriter &data) const
{
}
