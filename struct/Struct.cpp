#include "Struct.h"

#include "DryRunWriter.h"
#include <limits>
#include <fstream>

//std::ofstream log("memory.log");


quint32 Struct::memoryAddress(const Struct *pointer)
{
    if (pointer == NULL)
        return 0;
    return pointer->structStart;
}


Struct::Struct()
    : structStart(0)
    , dataStart(0)
    , dataEnd(0)
{
}

Struct::~Struct()
{
}

quint32 Struct::setMemoryAddress(MemoryModel const &memoryModel, quint32 baseAddress)
{
//    log << typeName() << "@" << this << ": computing memory size" << std::endl;

    QPair<quint32, quint32> memorySize = computeMemorySize(memoryModel, baseAddress);

    structStart = DataWriter::align(baseAddress, memoryModel.alignmentInBytes(alignment()));
    dataStart = structStart + memorySize.first - (structStart - baseAddress);
    dataEnd = dataStart + memorySize.second;

//    log << memorySize.first << ", " << memorySize.second << "\n";
//    log << typeName() << "@" << this << ": " << std::hex << structStart << " - " << dataStart << " - " << dataEnd << std::endl;

    return baseAddress + memorySize.first;
}

QPair<quint32, quint32> Struct::computeMemorySize(MemoryModel const &memoryModel, quint32 baseAddress) const
{
    quint32 structSize;
    {
        DryRunWriter dryRun(memoryModel, baseAddress);
        dryRun.align(alignment());
        writeStruct(dryRun);
        structSize = dryRun.memorySize();
    }

    baseAddress += structSize;

    quint32 dataSize;
    {
        DryRunWriter dryRun(memoryModel, baseAddress);
        writeData(dryRun);
        dataSize = dryRun.memorySize();
    }

    return qMakePair(structSize, dataSize);
}

void Struct::writeData(DataWriter &data) const
{
}

void Struct::write(DataWriter &data) const
{
    if (structStart == std::numeric_limits<quint32>::max())
        return;

//    log << typeName() << "@" << this << ": write starts" << std::endl;

    data.align(alignment());

    data.start(typeName(), structStart);

    data.verifyPosition(structStart, dataStart);
    writeStruct(data);
    data.verifyPosition(dataStart, dataEnd);
    writeData(data);
    data.verifyPosition(dataEnd, 0);

    data.end(typeName(), dataEnd);

//    log << typeName() << "@" << this << ": write ends" << std::endl;
}
