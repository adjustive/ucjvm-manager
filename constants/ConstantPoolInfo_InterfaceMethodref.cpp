#include "ConstantPoolInfo_InterfaceMethodref.h"
#include "ConstantPoolVisitor.h"

ConstantPoolInfo_InterfaceMethodref::ConstantPoolInfo_InterfaceMethodref(QDataStream &data)
{
}

void ConstantPoolInfo_InterfaceMethodref::print() const
{
}

void ConstantPoolInfo_InterfaceMethodref::accept(ConstantPoolVisitor &v) const
{
	v.visit(*this);
}
