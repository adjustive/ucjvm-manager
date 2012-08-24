#ifndef CONSTANTPOOLINFO_FIELDREF_H
#define CONSTANTPOOLINFO_FIELDREF_H

#include <QDataStream>

#include "ConstantPoolInfo.h"

class ConstantPoolInfo_Fieldref : public ConstantPoolInfo
{
public:
    ConstantPoolInfo_Fieldref(QDataStream &data);

    void print() const;

private:
    quint16 nameIndex;
    quint16 descriptorIndex;
};

#endif // CONSTANTPOOLINFO_FIELDREF_H
