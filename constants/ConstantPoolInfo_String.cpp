#include "ConstantPoolInfo_String.h"

ConstantPoolInfo_String::ConstantPoolInfo_String(QDataStream &data)
{
    data >> nameIndex;
}

void ConstantPoolInfo_String::print() const
{
    qDebug("String %d", nameIndex);
}
