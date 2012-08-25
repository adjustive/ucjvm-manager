#ifndef DRYRUNWRITER_H
#define DRYRUNWRITER_H

#include "DataWriter.h"

class DryRunWriter : public DataWriter
{
private:
    bool nullOk() const { return true; }

    void checkAlign(int alignment) const { Q_UNUSED(alignment); }

public:
    DryRunWriter();

    void write8 (quint8 ) { }
    void write16(quint16) { }
    void write32(quint32) { }
    void write64(quint64) { }
    void writeFloat(float) { }
    void writeDouble(double) { }

    char const *name() const { return "DryRunWriter"; }
};

#endif // DRYRUNWRITER_H
