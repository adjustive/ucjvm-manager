#include "ConstantPoolInfo_Methodref.h"
#include "ConstantPoolVisitor.h"

#include <QDataStream>

ConstantPoolInfo_Methodref::ConstantPoolInfo_Methodref(QDataStream &data)
{
    data >> d.nameIndex;
    data >> d.descriptorIndex;
}

quint16 ConstantPoolInfo_Methodref::nameIndex() const
{
    return d.nameIndex;
}

quint16 ConstantPoolInfo_Methodref::descriptorIndex() const
{
    return d.descriptorIndex;
}

void ConstantPoolInfo_Methodref::print() const
{
    qDebug("Methodref %d, %d", d.nameIndex, d.descriptorIndex);
}

void ConstantPoolInfo_Methodref::accept(ConstantPoolVisitor &v) const
{
	v.visit(*this);
}
