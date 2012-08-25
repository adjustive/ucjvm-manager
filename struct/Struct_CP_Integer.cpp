#include "Struct_CP_Integer.h"

#include "ConstantPoolInfo_Integer.h"
#include "DataWriter.h"

#include <QTextStream>

Struct_CP_Integer::Struct_CP_Integer(const ConstantPoolInfo_Integer &v)
    : value(v.value())
{
}

void Struct_CP_Integer::writeStruct(DataWriter &data) const
{
    Struct_CP::writeStruct(data);
    data.put32(value);
}

quint32 Struct_CP_Integer::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);
    return baseAddress;
}

void Struct_CP_Integer::printMemoryMap(QTextStream &ts) const
{
    ts << "Integer @0x" << memoryAddress << " = " << value << "\n";
}
