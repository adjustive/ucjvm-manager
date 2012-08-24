#ifndef CONSTANTPOOLINFO_FLOAT_H
#define CONSTANTPOOLINFO_FLOAT_H

#include <QDataStream>

#include "ConstantPoolInfo.h"

struct ConstantPoolInfo_FloatPrivate
{
    float value;
};

class ConstantPoolInfo_Float : public ConstantPoolInfo
{
public:
    ConstantPoolInfo_Float(QDataStream &data);

    float value() const;

    void print() const;
    void accept(ConstantPoolVisitor &v) const;

private:
    ConstantPoolInfo_FloatPrivate d;
};

#endif // CONSTANTPOOLINFO_FLOAT_H
