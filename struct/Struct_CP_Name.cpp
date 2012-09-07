#include "Struct_CP_Name.h"

#include "ConstantPoolInfo_NameAndType.h"
#include "DataWriter.h"

#include <QTextStream>

Struct_CP_Name::Struct_CP_Name(const ConstantPoolInfo_NameAndType &v)
    : nameIndex(v.nameIndex())
    , descriptorIndex(v.descriptorIndex())
{
}

void Struct_CP_Name::resolveClassReferences(const ResolveContext &context)
{
}

void Struct_CP_Name::writeConstantData(DataWriter &data) const
{
    data.put16(nameIndex, "nameIndex");
    data.put16(descriptorIndex, "descriptorIndex");
}

quint32 Struct_CP_Name::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);
    return baseAddress;
}

void Struct_CP_Name::printMemoryMap(QTextStream &ts) const
{
    ts << "Name @0x" << structStart << " = " << nameIndex << ", " << descriptorIndex << "\n";
}
