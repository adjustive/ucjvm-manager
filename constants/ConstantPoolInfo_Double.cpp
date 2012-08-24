#include "ConstantPoolInfo_Double.h"

ConstantPoolInfo_Double::ConstantPoolInfo_Double(QDataStream &data)
{
    data.setFloatingPointPrecision(QDataStream::DoublePrecision);
    data >> value;
}

void ConstantPoolInfo_Double::print() const
{
    qDebug("Double %f", value);
}
