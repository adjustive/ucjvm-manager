#include "ConstantPoolInfo_Fieldref.h"
#include "ConstantPoolVisitor.h"

ConstantPoolInfo_Fieldref::ConstantPoolInfo_Fieldref(QDataStream &data)
{
    data >> d.nameIndex;
    data >> d.descriptorIndex;
}

quint16 ConstantPoolInfo_Fieldref::nameIndex() const
{
    return d.nameIndex;
}

quint16 ConstantPoolInfo_Fieldref::descriptorIndex() const
{
    return d.descriptorIndex;
}

void ConstantPoolInfo_Fieldref::print() const
{
    qDebug("Fieldref %d, %d", d.nameIndex, d.descriptorIndex);
}

void ConstantPoolInfo_Fieldref::accept(ConstantPoolVisitor &v) const
{
	v.visit(*this);
}
