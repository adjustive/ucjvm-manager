#ifndef MEMORYWRITER_H
#define MEMORYWRITER_H

#include "DataWriter.h"

#include <QDataStream>

class MemoryWriter : public DataWriter
{
private:
    bool nullOk() const { return false; }

    void write8(quint8 value);
    void write16(quint16 value);
    void write32(quint32 value);
    void write64(quint64 value);
    void writeFloat(float value);
    void writeDouble(double value);

public:
    MemoryWriter(quint32 baseAddress);

    char const *name() const { return "MemoryWriter"; }

    int size() const { return array.size(); }
    QByteArray data() const { return array; }

private:
    QByteArray array;
    QDataStream stream;
};

#endif // MEMORYWRITER_H
