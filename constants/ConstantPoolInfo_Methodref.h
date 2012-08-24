#ifndef CONSTANTPOOLINFO_METHODREF_H
#define CONSTANTPOOLINFO_METHODREF_H

#include <QDataStream>

#include "ConstantPoolInfo.h"

class ConstantPoolInfo_Methodref : public ConstantPoolInfo
{
public:
    ConstantPoolInfo_Methodref(QDataStream &data);

    void print() const;

private:
    quint16 nameIndex;
    quint16 descriptorIndex;
};

#endif // CONSTANTPOOLINFO_METHODREF_H
