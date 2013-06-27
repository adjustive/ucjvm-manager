#include "Struct_CP_Double.h"

#include "ConstantPoolInfo_Double.h"
#include "DataWriter.h"

#include <QTextStream>

Struct_CP_Double::Struct_CP_Double(ConstantPoolInfo_Double const &v)
    : value(v.value())
{
}

void Struct_CP_Double::resolveClassReferences(const ResolveContext &context)
{
}

void Struct_CP_Double::writeConstantData(DataWriter &data) const
{
    data.putDouble(value, "value");
}

quint32 Struct_CP_Double::computeMemoryMap(MemoryModel const &memoryModel, quint32 baseAddress)
{
    baseAddress = setMemoryAddress(memoryModel, baseAddress);
    return baseAddress;
}

void Struct_CP_Double::printMemoryMap(QTextStream &ts) const
{
    ts << "Double @0x" << structStart << " = " << value << "\n";
}
