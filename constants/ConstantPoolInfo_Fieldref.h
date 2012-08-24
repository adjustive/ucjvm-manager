#ifndef CONSTANTPOOLINFO_FIELDREF_H
#define CONSTANTPOOLINFO_FIELDREF_H

#include <QDataStream>

#include "ConstantPoolInfo.h"

struct ConstantPoolInfo_FieldrefPrivate
{
    quint16 nameIndex;
    quint16 descriptorIndex;
};

class ConstantPoolInfo_Fieldref : public ConstantPoolInfo
{
public:
    ConstantPoolInfo_Fieldref(QDataStream &data);

    quint16 nameIndex() const;
    quint16 descriptorIndex() const;

    void print() const;
	void accept(ConstantPoolVisitor &v) const;

private:
    ConstantPoolInfo_FieldrefPrivate d;
};

#endif // CONSTANTPOOLINFO_FIELDREF_H
