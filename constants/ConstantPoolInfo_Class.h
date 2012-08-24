#ifndef CONSTANTPOOLINFO_CLASS_H
#define CONSTANTPOOLINFO_CLASS_H

#include <QDataStream>

#include "ConstantPoolInfo.h"

struct ConstantPoolInfo_ClassPrivate
{
    quint16 nameIndex;
};

class ConstantPoolInfo_Class : public ConstantPoolInfo
{
public:
    ConstantPoolInfo_Class(QDataStream &data);
    ConstantPoolInfo_Class(quint16 nameIndex);

    void print() const;

    quint16 nameIndex() const;

private:
    ConstantPoolInfo_ClassPrivate d;
};

#endif // CONSTANTPOOLINFO_CLASS_H
