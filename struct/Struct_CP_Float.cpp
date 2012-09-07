#include "Struct_CP_Float.h"

#include "ConstantPoolInfo_Float.h"
#include "DataWriter.h"

#include <QTextStream>

Struct_CP_Float::Struct_CP_Float(const ConstantPoolInfo_Float &v)
    : value(v.value())
{
}

void Struct_CP_Float::resolveClassReferences(const ResolveContext &context)
{
}

void Struct_CP_Float::writeConstantData(DataWriter &data) const
{
    data.putFloat(value, "value");
}

quint32 Struct_CP_Float::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);
    return baseAddress;
}

void Struct_CP_Float::printMemoryMap(QTextStream &ts) const
{
    ts << "Float @0x" << structStart << " = " << value << "\n";
}
