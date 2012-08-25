#include "Struct_CP_Method.h"

#include "Struct_Method.h"
#include "Struct_Class.h"
#include "ConstantPoolInfo_Methodref.h"
#include "DataWriter.h"

#include <QTextStream>

Struct_CP_Method::Struct_CP_Method(const ConstantPoolInfo_Methodref &v)
    : classIndex(v.nameIndex())
    , descriptorIndex(v.descriptorIndex())
    , address(0)
    , realClass(0)
{
}

void Struct_CP_Method::writeStruct(DataWriter &data) const
{
    Struct_CP::writeStruct(data);
    data.put16(classIndex);
    data.put16(descriptorIndex);
    data.putAddress(address);
    data.putAddress(realClass);
}

quint32 Struct_CP_Method::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);
    return baseAddress;
}

void Struct_CP_Method::printMemoryMap(QTextStream &ts) const
{
    ts << "Method @0x" << memoryAddress << " = " << classIndex << ", " << descriptorIndex << "\n";
}
