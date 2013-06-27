#include "ConstantPoolInfo_Double.h"
#include "ConstantPoolVisitor.h"

ConstantPoolInfo_Double::ConstantPoolInfo_Double(QDataStream &data)
{
    data.setFloatingPointPrecision(QDataStream::DoublePrecision);
    data >> d.value;
}

double ConstantPoolInfo_Double::value() const
{
    return d.value;
}

void ConstantPoolInfo_Double::print() const
{
    qDebug("Double %f", d.value);
}

void ConstantPoolInfo_Double::accept(ConstantPoolVisitor &v) const
{
	v.visit(*this);
}
