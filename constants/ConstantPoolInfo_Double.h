#ifndef CONSTANTPOOLINFO_DOUBLE_H
#define CONSTANTPOOLINFO_DOUBLE_H

#include <QDataStream>

#include "ConstantPoolInfo.h"

struct ConstantPoolInfo_DoublePrivate
{
    double value;
};

class ConstantPoolInfo_Double : public ConstantPoolInfo
{
public:
    ConstantPoolInfo_Double(QDataStream &data);

    double value() const;

    void print() const;
	void accept(ConstantPoolVisitor &v) const;

private:
    ConstantPoolInfo_DoublePrivate d;
};

#endif // CONSTANTPOOLINFO_DOUBLE_H
