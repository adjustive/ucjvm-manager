#include "Struct_ResourceName.h"

#include "DataWriter.h"

Struct_ResourceName::Struct_ResourceName(QString name)
    : name(name)
{
}


void Struct_ResourceName::writeStruct(DataWriter &data) const
{
    data.putBytes(name.toUtf8(), "data");
}

quint32 Struct_ResourceName::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);
    return baseAddress;
}

void Struct_ResourceName::printMemoryMap(QTextStream &ts) const
{
}
