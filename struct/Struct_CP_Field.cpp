#include "Struct_CP_Field.h"

#include "Struct_Field.h"
#include "Struct_Class.h"
#include "ConstantPoolInfo_Fieldref.h"
#include "DataWriter.h"

#include <QTextStream>

Struct_CP_Field::Struct_CP_Field(ConstantPoolInfo_Fieldref const &v)
    : classIndex(v.nameIndex())
    , descriptorIndex(v.descriptorIndex())
    , fieldAddress(0)
    , classAddress(0)
{
}

void Struct_CP_Field::writeStruct(DataWriter &data) const
{
    Struct_CP::writeStruct(data);
    data.put16(classIndex);
    data.put16(descriptorIndex);
    data.putAddress(fieldAddress);
    data.putAddress(classAddress);
}

quint32 Struct_CP_Field::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);
    return baseAddress;
}

void Struct_CP_Field::printMemoryMap(QTextStream &ts) const
{
    ts << "Field @0x" << memoryAddress << " = " << classIndex << ", " << descriptorIndex << "\n";
}
