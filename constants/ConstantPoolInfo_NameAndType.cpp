#include "ConstantPoolInfo_NameAndType.h"
#include "ConstantPoolVisitor.h"

#include <QDataStream>

ConstantPoolInfo_NameAndType::ConstantPoolInfo_NameAndType(QDataStream &data)
{
    data >> d.nameIndex;
    data >> d.descriptorIndex;
}

quint16 ConstantPoolInfo_NameAndType::nameIndex() const
{
    return d.nameIndex;
}

quint16 ConstantPoolInfo_NameAndType::descriptorIndex() const
{
    return d.descriptorIndex;
}

void ConstantPoolInfo_NameAndType::print() const
{
    qDebug("NameAndType %d, %d", d.nameIndex, d.descriptorIndex);
}

void ConstantPoolInfo_NameAndType::accept(ConstantPoolVisitor &v) const
{
	v.visit(*this);
}
