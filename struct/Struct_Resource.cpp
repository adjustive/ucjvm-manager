#include "Struct_Resource.h"

#include "DataWriter.h"


Struct_Resource::Struct_Resource(QString name)
    : name(name)
{
}


void Struct_Resource::writeStruct(DataWriter &data) const
{
    data.put16(this->data.size(), "size");
    data.put16(0, "type");
    data.putAddress(name, "name");
    data.putBytes(this->data, "data");
}

void Struct_Resource::writeData(DataWriter &data) const
{
    name.write(data);
}


quint32 Struct_Resource::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);

    baseAddress = name.computeMemoryMap(baseAddress);

    return baseAddress;
}


void Struct_Resource::printMemoryMap(QTextStream &ts) const
{
}
