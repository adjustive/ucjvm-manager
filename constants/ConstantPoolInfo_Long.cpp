#include "ConstantPoolInfo_Long.h"
#include "ConstantPoolVisitor.h"

#include <QDataStream>

ConstantPoolInfo_Long::ConstantPoolInfo_Long(QDataStream &data)
{
    data >> d.value;
}

quint64 ConstantPoolInfo_Long::value() const
{
    return d.value;
}

void ConstantPoolInfo_Long::print() const
{
    qDebug("Long %lld", d.value);
}

void ConstantPoolInfo_Long::accept(ConstantPoolVisitor &v) const
{
	v.visit(*this);
}

