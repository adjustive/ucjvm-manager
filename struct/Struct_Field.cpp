#include "Struct_Field.h"

#include "Field.h"
#include "DataWriter.h"

#include <QTextStream>

Struct_Field::Struct_Field(Field const &field)
    : accessFlags(field.accessFlags())
    , dataOffset(0)
    , constantValueReference(field.constantValueIndex())
    , fieldType(field.dataType())

    , nameIndex(field.nameIndex())
    , descriptorIndex(field.descriptorIndex())
    , name(field.name())
    , descriptor(field.descriptor())

    , dataSize(field.dataSize())
{
}


quint16 Struct_Field::setDataOffset(quint16 base)
{
    dataOffset = base;
    return dataSize;
}

bool Struct_Field::isStatic() const
{
    return accessFlags & Field::ACC_STATIC;
}


void Struct_Field::writeStruct(DataWriter &data) const
{
    data.put16(accessFlags, "accessFlags");
    data.put16(dataOffset, "dataOffset");
    data.put16(constantValueReference, "constantValueReference");
    data.put8(fieldType, "fieldType");
    data.pad8();
}

quint32 Struct_Field::computeMemoryMap(MemoryModel const &memoryModel, quint32 baseAddress)
{
    baseAddress = setMemoryAddress(memoryModel, baseAddress);
    return baseAddress;
}

void Struct_Field::printMemoryMap(QTextStream &ts) const
{
    ts << "      Field @0x" << structStart << " { offset = " << dataOffset << " }\n";
}
