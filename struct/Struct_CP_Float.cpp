#include "Struct_CP_Float.h"

#include "ConstantPoolInfo_Float.h"
#include "DataWriter.h"

#include <QTextStream>

Struct_CP_Float::Struct_CP_Float(const ConstantPoolInfo_Float &v)
    : value(v.value())
{
}

void Struct_CP_Float::writeStruct(DataWriter &data) const
{
    Struct_CP::writeStruct(data);
    data.putFloat(value);
}

quint32 Struct_CP_Float::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);
    return baseAddress;
}

void Struct_CP_Float::printMemoryMap(QTextStream &ts) const
{
    ts << "Float @0x" << memoryAddress << " = " << value << "\n";
}
