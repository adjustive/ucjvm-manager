#ifndef DRYRUNWRITER_H
#define DRYRUNWRITER_H

#include "DataWriter.h"

class DryRunWriter : public DataWriter
{
public:
    DryRunWriter();

    void put8 (quint8 ) { memorySize += 1; }
    void put16(quint16) { memorySize += 2; }
    void put32(quint32) { memorySize += 4; }
    void put64(quint64) { memorySize += 8; }
    void put(QByteArray value) { memorySize += value.size(); }

public:
    quint32 memorySize;
};

#endif // DRYRUNWRITER_H
