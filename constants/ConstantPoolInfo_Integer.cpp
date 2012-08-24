#include "ConstantPoolInfo_Integer.h"

ConstantPoolInfo_Integer::ConstantPoolInfo_Integer(QDataStream &data)
{
    data >> value;
}

void ConstantPoolInfo_Integer::print() const
{
    qDebug("Integer %d", value);
}
