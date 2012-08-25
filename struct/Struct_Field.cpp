#include "Struct_Field.h"

#include "Field.h"
#include "DataWriter.h"

#include <QTextStream>

Struct_Field::Struct_Field(Field const &field)
    : accessFlags(field.accessFlags())
    , dataOffset(0)
    , constantValueReference(field.constantValueIndex())
    , fieldType(field.dataType())
{
}

void Struct_Field::writeStruct(DataWriter &data) const
{
    data.put16(accessFlags);
    data.put16(dataOffset);
    data.put16(constantValueReference);
    data.put8(fieldType);
    data.pad8();
}

quint32 Struct_Field::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);
    return baseAddress;
}

void Struct_Field::printMemoryMap(QTextStream &ts) const
{
    ts << "      Field @0x" << memoryAddress << " { offset = " << dataOffset << " }\n";
}
