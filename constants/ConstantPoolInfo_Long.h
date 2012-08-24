#ifndef CONSTANTPOOLINFO_LONG_H
#define CONSTANTPOOLINFO_LONG_H

#include <QDataStream>

#include "ConstantPoolInfo.h"

class ConstantPoolInfo_Long : public ConstantPoolInfo
{
public:
    ConstantPoolInfo_Long(QDataStream &data);

    void print() const;

private:
    qint64 value;
};

#endif // CONSTANTPOOLINFO_LONG_H
