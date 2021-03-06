#include "MemoryWriter.h"

MemoryWriter::MemoryWriter(MemoryModel const &memoryModel, quint32 baseAddress)
    : DataWriter(memoryModel, baseAddress)
    , stream(&array, QIODevice::WriteOnly)
{
    switch (memoryModel.byteOrder())
    {
    case MemoryModel::BigEndian:
        stream.setByteOrder(QDataStream::BigEndian);
        break;
    case MemoryModel::LittleEndian:
        stream.setByteOrder(QDataStream::LittleEndian);
        break;
    }

    array.reserve(128 * 1024);
}

void MemoryWriter::write8(quint8 value)
{
    stream << value;
}

void MemoryWriter::write16(quint16 value)
{
    stream << value;
}

void MemoryWriter::write32(quint32 value)
{
    stream << value;
}

void MemoryWriter::write64(quint64 value)
{
    stream << value;
}

void MemoryWriter::writeFloat(float value)
{
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    stream << value;
}

void MemoryWriter::writeDouble(double value)
{
    stream.setFloatingPointPrecision(QDataStream::DoublePrecision);
    stream << value;
}


void MemoryWriter::start(const char *section, quint32 address)
{
    if (address - baseAddress != size())
        qFatal("address %x in %s is not expected %x", size(), section, address);
}

void MemoryWriter::end(const char *section, quint32 address)
{
    if (address - baseAddress != size())
        qFatal("address %x in %s is not expected %x", size(), section, address);
}
