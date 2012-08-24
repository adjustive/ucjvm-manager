#ifndef CONSTANTPOOLINFO_NAMEANDTYPE_H
#define CONSTANTPOOLINFO_NAMEANDTYPE_H

#include <QDataStream>

#include "ConstantPoolInfo.h"

class ConstantPoolInfo_NameAndType : public ConstantPoolInfo
{
public:
    ConstantPoolInfo_NameAndType(QDataStream &data);

    void print() const;

private:
    quint16 nameIndex;
    quint16 descriptorIndex;
};

#endif // CONSTANTPOOLINFO_NAMEANDTYPE_H
