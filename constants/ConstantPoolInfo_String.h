#ifndef CONSTANTPOOLINFO_STRING_H
#define CONSTANTPOOLINFO_STRING_H

#include <QDataStream>

#include "ConstantPoolInfo.h"

struct ConstantPoolInfo_StringPrivate
{
    quint16 nameIndex;
};

class ConstantPoolInfo_String : public ConstantPoolInfo
{
public:
    ConstantPoolInfo_String(QDataStream &data);

    quint16 nameIndex() const;

    void print() const;
	void accept(ConstantPoolVisitor &v) const;

private:
    ConstantPoolInfo_StringPrivate d;
};

#endif // CONSTANTPOOLINFO_STRING_H
