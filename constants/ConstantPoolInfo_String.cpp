#include "ConstantPoolInfo_String.h"
#include "ConstantPoolVisitor.h"

ConstantPoolInfo_String::ConstantPoolInfo_String(QDataStream &data)
{
    data >> d.nameIndex;
}

quint16 ConstantPoolInfo_String::nameIndex() const
{
    return d.nameIndex;
}

void ConstantPoolInfo_String::print() const
{
    qDebug("String %d", d.nameIndex);
}

void ConstantPoolInfo_String::accept(ConstantPoolVisitor &v) const
{
	v.visit(*this);
}
