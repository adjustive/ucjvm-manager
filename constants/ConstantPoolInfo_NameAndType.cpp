#include "ConstantPoolInfo_NameAndType.h"

ConstantPoolInfo_NameAndType::ConstantPoolInfo_NameAndType(QDataStream &data)
{
    data >> nameIndex;
    data >> descriptorIndex;
}

void ConstantPoolInfo_NameAndType::print() const
{
    qDebug("NameAndType %d, %d", nameIndex, descriptorIndex);
}
