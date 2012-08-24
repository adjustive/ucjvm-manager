#include "Struct.h"

#include "DryRunWriter.h"

Struct::Struct()
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
    writeThis(dryRun);
    return dryRun.memorySize;
}

void Struct::writeChildren(DataWriter &data) const
{
    Q_UNUSED(data);
}

void Struct::write(DataWriter &data) const
{
    writeThis(data);
    writeChildren(data);
}
