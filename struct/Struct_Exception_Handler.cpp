#include "Struct_Exception_Handler.h"

Struct_Exception_Handler::Struct_Exception_Handler()
{
}

void Struct_Exception_Handler::writeStruct(DataWriter &data) const
{
}

quint32 Struct_Exception_Handler::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);
    return baseAddress;
}

void Struct_Exception_Handler::printMemoryMap(QTextStream &ts) const
{
}
