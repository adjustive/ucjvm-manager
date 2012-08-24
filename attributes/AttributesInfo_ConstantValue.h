#ifndef ATTRIBUTESINFO_CONSTANTVALUE_H
#define ATTRIBUTESINFO_CONSTANTVALUE_H

#include "AttributesInfo.h"

struct AttributesInfo_ConstantValuePrivate
{
    quint16 constantValueIndex;
};

class AttributesInfo_ConstantValue : public AttributesInfo
{
public:
    AttributesInfo_ConstantValue(QDataStream &data);

    quint16 constantValueIndex() const;

private:
    AttributesInfo_ConstantValuePrivate d;
};

#endif // ATTRIBUTESINFO_CONSTANTVALUE_H
