#include "Struct_CP_Integer.h"

#include "ConstantPoolInfo_Integer.h"
#include "DataWriter.h"

#include <QTextStream>

Struct_CP_Integer::Struct_CP_Integer(const ConstantPoolInfo_Integer &v)
    : value(v.value())
{
}

void Struct_CP_Integer::resolveClassReferences(const ResolveContext &context)
{
}

void Struct_CP_Integer::writeConstantData(DataWriter &data) const
{
    data.put32(value, "value");
}

quint32 Struct_CP_Integer::computeMemoryMap(MemoryModel const &memoryModel, quint32 baseAddress)
{
    baseAddress = setMemoryAddress(memoryModel, baseAddress);
    return baseAddress;
}

void Struct_CP_Integer::printMemoryMap(QTextStream &ts) const
{
    ts << "Integer @0x" << structStart << " = " << value << "\n";
}
