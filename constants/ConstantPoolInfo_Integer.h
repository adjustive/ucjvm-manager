#ifndef CONSTANTPOOLINFO_INTEGER_H
#define CONSTANTPOOLINFO_INTEGER_H

#include <QDataStream>

#include "ConstantPoolInfo.h"

class ConstantPoolInfo_Integer : public ConstantPoolInfo
{
public:
    ConstantPoolInfo_Integer(QDataStream &data);

    void print() const;

private:
    qint32 value;
};

#endif // CONSTANTPOOLINFO_INTEGER_H
