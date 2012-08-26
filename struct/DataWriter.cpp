#include "DataWriter.h"

#include "Struct.h"

#include <typeinfo>

enum Size
{
    BYTE_SIZE   = 1,
    BYTE_ALIGN  = 1,
    SHORT_SIZE  = 2,
    SHORT_ALIGN = 2,
    INT_SIZE    = 4,
    INT_ALIGN   = 4,
    LONG_SIZE   = 8,
    LONG_ALIGN  = 8,

    FLOAT_SIZE  = 4,
    FLOAT_ALIGN = 4,
    DOUBLE_SIZE = 8,
    DOUBLE_ALIGN= 8,

    ADDRESS_SIZE = INT_SIZE,
    ADDRESS_ALIGN = INT_ALIGN
};

DataWriter::DataWriter(quint32 baseAddress)
    : written(0)
    , baseAddress(baseAddress)
{
//    qDebug("new DataWriter");
}

void DataWriter::wrote(int bytes)
{
    written += bytes;
}

quint32 DataWriter::memorySize() const
{
    return written;
}

void DataWriter::checkAlign(int alignment) const
{
    if (memorySize() % alignment != 0)
        qWarning("alignment at %d is less than %d", written, alignment);
}

void DataWriter::setAlign(int alignment)
{
    while (memorySize() % alignment != 0)
        pad8();
}

void DataWriter::position(quint32 pos) const
{
    if (pos != memorySize() && !nullOk())
        qWarning("expected position %u is not actual %u", pos, memorySize());
}

void DataWriter::align8()
{
    setAlign(BYTE_ALIGN);
}

void DataWriter::align16()
{
    setAlign(SHORT_ALIGN);
}

void DataWriter::align32()
{
    setAlign(INT_ALIGN);
}

void DataWriter::align64()
{
    setAlign(LONG_ALIGN);
}

void DataWriter::alignFloat()
{
    setAlign(FLOAT_ALIGN);
}

void DataWriter::alignDouble()
{
    setAlign(DOUBLE_ALIGN);
}

void DataWriter::alignAddress()
{
    setAlign(ADDRESS_ALIGN);
}


void DataWriter::put8(quint8 value)
{
//    checkAlign(BYTE_ALIGN);
	write8(value);
    wrote(BYTE_SIZE);
}

void DataWriter::put16(quint16 value)
{
    checkAlign(SHORT_ALIGN);
    write16(value);
    wrote(SHORT_SIZE);
}

void DataWriter::put32(quint32 value)
{
    checkAlign(INT_ALIGN);
    write32(value);
    wrote(INT_SIZE);
}

void DataWriter::put64(quint64 value)
{
    checkAlign(LONG_ALIGN);
    write64(value);
    wrote(LONG_SIZE);
}

void DataWriter::putFloat(float value)
{
    checkAlign(FLOAT_ALIGN);
    writeFloat(value);
    wrote(FLOAT_SIZE);
}

void DataWriter::putDouble(double value)
{
    checkAlign(DOUBLE_ALIGN);
	writeDouble(value);
    wrote(DOUBLE_SIZE);
}

void DataWriter::putBytes(QByteArray value)
{
    foreach (char byte, value)
        write8(byte);
    wrote(value.size());
}

void DataWriter::putAddress(Struct const &reference)
{
    if (reference.memoryAddress == 0)
    {
        if (!nullOk())
            qWarning("memory address for %p (%s) is NULL", &reference, typeid(reference).name());
    }
    else if (reference.memoryAddress < baseAddress)
    {
        qFatal("memory address 0x%x is below base address 0x%x", reference.memoryAddress, baseAddress);
    }

    put32(reference.memoryAddress);
}

void DataWriter::putAddress(Struct const *pointer)
{
    if (pointer)
        putAddress(*pointer);
    else
        put32(0);
}

void DataWriter::putAddress(QSharedPointer<Struct> pointer)
{
    putAddress(pointer.data());
}

void DataWriter::pad8()
{
    put8(0);
}

void DataWriter::pad16()
{
    put16(0);
}

void DataWriter::pad32()
{
    put32(0);
}

void DataWriter::pad64()
{
    put64(0);
}
