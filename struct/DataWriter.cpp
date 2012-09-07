#include "DataWriter.h"

#include "Struct.h"

#include <limits>

DataWriter::DataWriter(quint32 baseAddress)
    : baseAddress(baseAddress)
    , nextAddress(0)
    , currentAddress(baseAddress)
{
}

void DataWriter::wrote(quint16 bytes)
{
    if (!permissive())
    {
        if (nextAddress != 0)
        {
            quint32 actual = currentAddress + bytes - baseAddress;
            quint32 expected = nextAddress - baseAddress;
//            qDebug("%u > %u", actual, expected);
            if (actual > expected)
                qFatal("wrote %u bytes beyond expected size", actual - expected);
        }
    }
    currentAddress += bytes;
//    log << typeName() << " ~ " << currentAddress << " : " << bytes << std::endl;
}

quint32 DataWriter::memorySize() const
{
    return currentAddress - baseAddress;
}

void DataWriter::checkAlign(Size alignment) const
{
#if 0
    if (!permissive())
    {
        if (currentAddress % alignment != 0)
            qWarning("alignment at %u is less than %u", currentAddress, alignment);
    }
#endif
}

quint32 DataWriter::align(quint32 address, quint8 alignment)
{
    return (address & ~(alignment - 1)) + alignment * !!(address & (alignment - 1));
}

void DataWriter::align(quint8 alignment)
{
//    if (currentAddress % alignment != 0)
//    {
//        log << "aligning to " << uint(alignment) << std::endl;
        while (currentAddress % alignment != 0)
            pad8();
//        log << "aligning complete" << std::endl;
//    }
}

void DataWriter::verifyPosition(quint32 currentAddress, quint32 nextAddress)
{
    if (!permissive())
    {
        if (currentAddress < baseAddress)
            qFatal("memory address 0x%x is below base address 0x%x", currentAddress, baseAddress);

        quint32 relativeAddress = currentAddress - baseAddress;
        if (relativeAddress != memorySize())
            qFatal("expected position %u is not actual %u", relativeAddress, memorySize());
    }
    this->nextAddress = nextAddress;
}


void DataWriter::put8(quint8 value, const char *field)
{
    start(field, currentAddress);
    checkAlign(BYTE_ALIGN);
	write8(value);
    wrote(BYTE_SIZE);
    end(field, currentAddress);
}

void DataWriter::put16(quint16 value, char const *field)
{
    start(field, currentAddress);
    checkAlign(SHORT_ALIGN);
    write16(value);
    wrote(SHORT_SIZE);
    end(field, currentAddress);
}

void DataWriter::put32(quint32 value, const char *field)
{
    start(field, currentAddress);
    checkAlign(INT_ALIGN);
    write32(value);
    wrote(INT_SIZE);
    end(field, currentAddress);
}

void DataWriter::put64(quint64 value, const char *field)
{
    start(field, currentAddress);
    checkAlign(LONG_ALIGN);
    write64(value);
    wrote(LONG_SIZE);
    end(field, currentAddress);
}

void DataWriter::putFloat(float value, const char *field)
{
    start(field, currentAddress);
    checkAlign(FLOAT_ALIGN);
    writeFloat(value);
    wrote(FLOAT_SIZE);
    end(field, currentAddress);
}

void DataWriter::putDouble(double value, const char *field)
{
    start(field, currentAddress);
    checkAlign(DOUBLE_ALIGN);
	writeDouble(value);
    wrote(DOUBLE_SIZE);
    end(field, currentAddress);
}

void DataWriter::putBytes(QByteArray value, const char *field)
{
    start(field, currentAddress);
    foreach (char byte, value)
        write8(byte);
    wrote(value.size());
    end(field, currentAddress);
}

void DataWriter::putAddress(Struct const &reference, const char *field)
{
    if (!permissive())
    {
        if (reference.structStart == 0)
            qWarning("memory address for %p (%s) is NULL", &reference, reference.typeName());
        else if (reference.structStart < baseAddress)
            qFatal("memory address 0x%x is below base address 0x%x", reference.structStart, baseAddress);
    }

    put32(reference.structStart, field);
}

void DataWriter::putAddress(Struct const *pointer, const char *field)
{
    if (pointer)
        putAddress(*pointer, field);
    else
        put32(0, field);
}

void DataWriter::putAddress(QSharedPointer<Struct> pointer, const char *field)
{
    putAddress(pointer.data(), field);
}

void DataWriter::pad8()
{
    put8(0, "__pad8");
}

void DataWriter::pad16()
{
    put16(0, "__pad16");
}

void DataWriter::pad32()
{
    put32(0, "__pad32");
}

void DataWriter::pad64()
{
    put64(0, "__pad64");
}


void DataWriter::start(const char *section, quint32 address)
{
    Q_UNUSED(section);
    Q_UNUSED(address);
}

void DataWriter::end(const char *section, quint32 address)
{
    Q_UNUSED(section);
    Q_UNUSED(address);
}
