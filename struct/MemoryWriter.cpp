#include "MemoryWriter.h"

MemoryWriter::MemoryWriter()
    : stream(&data, QIODevice::WriteOnly)
{
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
    stream << value;
}

void MemoryWriter::writeDouble(double value)
{
    stream << value;
}
