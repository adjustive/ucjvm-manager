#include "Struct_Exceptions.h"

Struct_Exceptions::Struct_Exceptions()
{
}

void Struct_Exceptions::writeStruct(DataWriter &data) const
{
}

quint32 Struct_Exceptions::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);
    return baseAddress;
}

void Struct_Exceptions::printMemoryMap(QTextStream &ts) const
{
}
