#ifndef CONSTANTPOOLINFO_FLOAT_H
#define CONSTANTPOOLINFO_FLOAT_H

#include <QDataStream>

#include "ConstantPoolInfo.h"

class ConstantPoolInfo_Float : public ConstantPoolInfo
{
public:
    ConstantPoolInfo_Float(QDataStream &data);

    void print() const;

private:
    float value;
};

#endif // CONSTANTPOOLINFO_FLOAT_H
