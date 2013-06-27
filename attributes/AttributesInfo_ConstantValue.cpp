#include "AttributesInfo_ConstantValue.h"

#include <QDataStream>

AttributesInfo_ConstantValue::AttributesInfo_ConstantValue(QDataStream &data)
{
    data >> d.constantValueIndex;
}

quint16 AttributesInfo_ConstantValue::constantValueIndex() const
{
    return d.constantValueIndex;
}
