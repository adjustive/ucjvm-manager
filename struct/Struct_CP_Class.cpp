#include "Struct_CP_Class.h"

#include "Struct_Class.h"
#include "ConstantPoolInfo_Class.h"
#include "DataWriter.h"

#include <QTextStream>

Struct_CP_Class::Struct_CP_Class(const ConstantPoolInfo_Class &v)
    : index(v.nameIndex())
    , classAddress(0)
{
}

void Struct_CP_Class::writeStruct(DataWriter &data) const
{
    Struct_CP::writeStruct(data);
    data.put16(index);
    data.putAddress(classAddress);
}

quint32 Struct_CP_Class::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);
    return baseAddress;
}

void Struct_CP_Class::printMemoryMap(QTextStream &ts) const
{
    ts << "Class @0x" << memoryAddress << " -> " << index << "\n";
}
