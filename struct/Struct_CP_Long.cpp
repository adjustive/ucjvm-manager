#include "Struct_CP_Long.h"

#include "ConstantPoolInfo_Long.h"
#include "DataWriter.h"

#include <QTextStream>

Struct_CP_Long::Struct_CP_Long(const ConstantPoolInfo_Long &v)
    : value(v.value())
{
}

void Struct_CP_Long::resolveClassReferences(const ResolveContext &context)
{
}

void Struct_CP_Long::writeConstantData(DataWriter &data) const
{
    data.put64(value, "value");
}

quint32 Struct_CP_Long::computeMemoryMap(MemoryModel const &memoryModel, quint32 baseAddress)
{
    baseAddress = setMemoryAddress(memoryModel, baseAddress);
    return baseAddress;
}

void Struct_CP_Long::printMemoryMap(QTextStream &ts) const
{
    ts << "Long @0x" << structStart << " = " << value << "\n";
}
