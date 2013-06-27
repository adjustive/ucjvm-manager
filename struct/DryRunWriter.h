#ifndef DRYRUNWRITER_H
#define DRYRUNWRITER_H

#include "DataWriter.h"

class DryRunWriter : public DataWriter
{
private:
    bool permissive() const { return true; }

public:
    DryRunWriter(const MemoryModel &memoryModel, quint32 baseAddress);

    void write8 (quint8 ) { }
    void write16(quint16) { }
    void write32(quint32) { }
    void write64(quint64) { }
    void writeFloat(float) { }
    void writeDouble(double) { }

    char const *typeName() const { return "DryRunWriter"; }
};

#endif // DRYRUNWRITER_H
