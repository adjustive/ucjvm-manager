#include "DataWriter.h"

#include "Struct.h"

#include <typeinfo>

DataWriter::DataWriter()
{
}

void DataWriter::put(QByteArray value)
{
    foreach (char byte, value)
        put8(byte);
}

void DataWriter::putAddress(Struct const &reference)
{
    if (reference.memoryAddress == 0 && !nullOk())
        qWarning("memory address for %p (%s) is NULL", &reference, typeid(reference).name());
    put32(reference.memoryAddress);
}

void DataWriter::putAddress(Struct const *pointer)
{
    if (pointer)
        putAddress(*pointer);
    else
        put32(0);
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
