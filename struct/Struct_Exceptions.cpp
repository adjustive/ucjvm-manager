#include "Struct_Exceptions.h"

#include "DataWriter.h"

Struct_Exceptions::Struct_Exceptions()
{
}

void Struct_Exceptions::writeStruct(DataWriter &data) const
{
    data.put16(exceptions.size());
    data.pad16();

    foreach (quint16 exception, exceptions)
        data.put16(exception);
}

quint32 Struct_Exceptions::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);
    return baseAddress;
}

void Struct_Exceptions::printMemoryMap(QTextStream &ts) const
{
}

void Struct_Exceptions::add(QList<quint16> exceptions)
{
    this->exceptions.append(exceptions);
}

quint16 Struct_Exceptions::size() const
{
    return exceptions.size();
}
