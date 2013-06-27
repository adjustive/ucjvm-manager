#ifndef CONSTANTPOOLINFO_METHODREF_H
#define CONSTANTPOOLINFO_METHODREF_H

#include <QtGlobal>

#include "ConstantPoolInfo.h"

struct ConstantPoolInfo_MethodrefPrivate
{
    quint16 nameIndex;
    quint16 descriptorIndex;
};

class ConstantPoolInfo_Methodref : public ConstantPoolInfo
{
public:
    ConstantPoolInfo_Methodref(QDataStream &data);

    quint16 nameIndex() const;
    quint16 descriptorIndex() const;

    void print() const;
	void accept(ConstantPoolVisitor &v) const;

private:
    ConstantPoolInfo_MethodrefPrivate d;
};

#endif // CONSTANTPOOLINFO_METHODREF_H
