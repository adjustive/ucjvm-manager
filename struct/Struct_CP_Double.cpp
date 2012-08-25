#include "Struct_CP_Double.h"

#include "ConstantPoolInfo_Double.h"
#include "DataWriter.h"

#include <QTextStream>

Struct_CP_Double::Struct_CP_Double(ConstantPoolInfo_Double const &v)
    : value(v.value())
{
}

void Struct_CP_Double::writeStruct(DataWriter &data) const
{
    Struct_CP::writeStruct(data);
    data.putDouble(value);
}

quint32 Struct_CP_Double::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);
    return baseAddress;
}

void Struct_CP_Double::printMemoryMap(QTextStream &ts) const
{
    ts << "Double @0x" << memoryAddress << " = " << value << "\n";
}
