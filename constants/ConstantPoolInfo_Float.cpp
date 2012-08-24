#include "ConstantPoolInfo_Float.h"
#include "ConstantPoolVisitor.h"

ConstantPoolInfo_Float::ConstantPoolInfo_Float(QDataStream &data)
{
    data.setFloatingPointPrecision(QDataStream::SinglePrecision);
    data >> d.value;
}

float ConstantPoolInfo_Float::value() const
{
    return d.value;
}

void ConstantPoolInfo_Float::print() const
{
    qDebug("Float %f", d.value);
}

void ConstantPoolInfo_Float::accept(ConstantPoolVisitor &v) const
{
	v.visit(*this);
}
