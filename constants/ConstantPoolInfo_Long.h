#ifndef CONSTANTPOOLINFO_LONG_H
#define CONSTANTPOOLINFO_LONG_H

#include <QtGlobal>

#include "ConstantPoolInfo.h"

struct ConstantPoolInfo_LongPrivate
{
    quint64 value;
};

class ConstantPoolInfo_Long : public ConstantPoolInfo
{
public:
    ConstantPoolInfo_Long(QDataStream &data);

    quint64 value() const;

    void print() const;
    void accept(ConstantPoolVisitor &v) const;

private:
    ConstantPoolInfo_LongPrivate d;
};

#endif // CONSTANTPOOLINFO_LONG_H
