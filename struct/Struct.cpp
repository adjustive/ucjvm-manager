#include "Struct.h"

#include "DryRunWriter.h"

Struct::Struct()
    : memoryAddress(0)
{
}

Struct::~Struct()
{
}

quint32 Struct::setMemoryAddress(quint32 baseAddress)
{
    memoryAddress = baseAddress;
    return baseAddress + memorySize();
}

quint32 Struct::memorySize() const
{
    DryRunWriter dryRun;
    writeStruct(dryRun);
    return dryRun.memorySize();
}

void Struct::writeData(DataWriter &data) const
{
}

void Struct::write(DataWriter &data) const
{
    writeStruct(data);
    writeData(data);
}
