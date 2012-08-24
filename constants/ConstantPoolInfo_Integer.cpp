#include "ConstantPoolInfo_Integer.h"
#include "ConstantPoolVisitor.h"

ConstantPoolInfo_Integer::ConstantPoolInfo_Integer(QDataStream &data)
{
    data >> d.value;
}

quint32 ConstantPoolInfo_Integer::value() const
{
    return d.value;
}

void ConstantPoolInfo_Integer::print() const
{
    qDebug("Integer %d", d.value);
}

void ConstantPoolInfo_Integer::accept(ConstantPoolVisitor &v) const
{
	v.visit(*this);
}
