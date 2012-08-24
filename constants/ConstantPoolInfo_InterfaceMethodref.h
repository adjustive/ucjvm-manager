#ifndef CONSTANTPOOLINFO_INTERFACEMETHODREF_H
#define CONSTANTPOOLINFO_INTERFACEMETHODREF_H

#include <QDataStream>

#include "ConstantPoolInfo.h"

class ConstantPoolInfo_InterfaceMethodref : public ConstantPoolInfo
{
public:
    ConstantPoolInfo_InterfaceMethodref(QDataStream &data);

    void print() const;
};

#endif // CONSTANTPOOLINFO_INTERFACEMETHODREF_H
