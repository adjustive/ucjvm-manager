#include "Struct_CP_String.h"

#include "ConstantPoolInfo_String.h"
#include "DataWriter.h"

#include <QTextStream>

Struct_CP_String::Struct_CP_String(ConstantPoolInfo_String const &v)
    : stringIndex(v.nameIndex())
{
}

void Struct_CP_String::resolveClassReferences(const ResolveContext &context)
{
}

void Struct_CP_String::writeStruct(DataWriter &data) const
{
    Struct_CP::writeStruct(data);
    data.put16(stringIndex, "stringIndex");
}

quint32 Struct_CP_String::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);
    return baseAddress;
}

void Struct_CP_String::printMemoryMap(QTextStream &ts) const
{
    ts << "String @0x" << structStart << " = " << stringIndex << "\n";
}
