#include "ConstantPoolInfo_Methodref.h"

ConstantPoolInfo_Methodref::ConstantPoolInfo_Methodref(QDataStream &data)
{
    data >> nameIndex;
    data >> descriptorIndex;
}

void ConstantPoolInfo_Methodref::print() const
{
    qDebug("Methodref %d, %d", nameIndex, descriptorIndex);
}
