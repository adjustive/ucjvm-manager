#include "ConstantPoolInfo_Fieldref.h"

ConstantPoolInfo_Fieldref::ConstantPoolInfo_Fieldref(QDataStream &data)
{
    data >> nameIndex;
    data >> descriptorIndex;
}

void ConstantPoolInfo_Fieldref::print() const
{
    qDebug("Fieldref %d, %d", nameIndex, descriptorIndex);
}
