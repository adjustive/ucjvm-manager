#ifndef CONSTANTPOOLINFO_DOUBLE_H
#define CONSTANTPOOLINFO_DOUBLE_H

#include <QDataStream>

#include "ConstantPoolInfo.h"

class ConstantPoolInfo_Double : public ConstantPoolInfo
{
public:
    ConstantPoolInfo_Double(QDataStream &data);

    void print() const;

private:
    double value;
};

#endif // CONSTANTPOOLINFO_DOUBLE_H
