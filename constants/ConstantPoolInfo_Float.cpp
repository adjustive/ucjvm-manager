#include "ConstantPoolInfo_Float.h"

ConstantPoolInfo_Float::ConstantPoolInfo_Float(QDataStream &data)
{
    data.setFloatingPointPrecision(QDataStream::SinglePrecision);
    data >> value;
}

void ConstantPoolInfo_Float::print() const
{
    qDebug("Float %f", value);
}
