#ifndef CONSTANTPOOLINFO_INTEGER_H
#define CONSTANTPOOLINFO_INTEGER_H

#include <QDataStream>

#include "ConstantPoolInfo.h"

struct ConstantPoolInfo_IntegerPrivate
{
    quint32 value;
};

class ConstantPoolInfo_Integer : public ConstantPoolInfo
{
public:
    ConstantPoolInfo_Integer(QDataStream &data);

    quint32 value() const;

    void print() const;
    void accept(ConstantPoolVisitor &v) const;

private:
    ConstantPoolInfo_IntegerPrivate d;
};

#endif // CONSTANTPOOLINFO_INTEGER_H
