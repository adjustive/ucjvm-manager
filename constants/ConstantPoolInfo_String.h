#ifndef CONSTANTPOOLINFO_STRING_H
#define CONSTANTPOOLINFO_STRING_H

#include <QDataStream>

#include "ConstantPoolInfo.h"

class ConstantPoolInfo_String : public ConstantPoolInfo
{
public:
    ConstantPoolInfo_String(QDataStream &data);

    void print() const;

private:
    quint16 nameIndex;
};

#endif // CONSTANTPOOLINFO_STRING_H
