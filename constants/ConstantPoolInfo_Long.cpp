#include "ConstantPoolInfo_Long.h"

ConstantPoolInfo_Long::ConstantPoolInfo_Long(QDataStream &data)
{
    data >> value;
}

void ConstantPoolInfo_Long::print() const
{
    qDebug("Long %lld", value);
}

