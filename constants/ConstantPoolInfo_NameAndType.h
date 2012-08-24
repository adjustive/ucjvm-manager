#ifndef CONSTANTPOOLINFO_NAMEANDTYPE_H
#define CONSTANTPOOLINFO_NAMEANDTYPE_H

#include <QtGlobal>

#include "ConstantPoolInfo.h"

struct ConstantPoolInfo_NameAndTypePrivate
{
    quint16 nameIndex;
    quint16 descriptorIndex;
};

class ConstantPoolInfo_NameAndType : public ConstantPoolInfo
{
public:
    ConstantPoolInfo_NameAndType(QDataStream &data);

    quint16 nameIndex() const;
    quint16 descriptorIndex() const;

    void print() const;
	void accept(ConstantPoolVisitor &v) const;

private:
    ConstantPoolInfo_NameAndTypePrivate d;
};

#endif // CONSTANTPOOLINFO_NAMEANDTYPE_H
