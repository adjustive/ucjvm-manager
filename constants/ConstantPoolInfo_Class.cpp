#include "ConstantPoolInfo_Class.h"

ConstantPoolInfo_Class::ConstantPoolInfo_Class(QDataStream &data)
{
    data >> d.nameIndex;
}

ConstantPoolInfo_Class::ConstantPoolInfo_Class(quint16 nameIndex)
{
    d.nameIndex = nameIndex;
}

void ConstantPoolInfo_Class::print() const
{
    qDebug("Class #%d", d.nameIndex);
}

quint16 ConstantPoolInfo_Class::nameIndex() const
{
    return d.nameIndex;
}
