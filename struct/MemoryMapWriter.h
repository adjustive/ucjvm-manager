#ifndef MEMORYMAPWRITER_H
#define MEMORYMAPWRITER_H

#include "DataWriter.h"

#include <QList>
#include <QTextStream>

class MemoryMapWriter : public DataWriter
{
    bool permissive() const { return false; }

public:
    MemoryMapWriter(quint32 baseAddress);

    void write8(quint8 value);
    void write16(quint16 value);
    void write32(quint32 value);
    void write64(quint64 value);
    void writeFloat(float value);
    void writeDouble(double value);

    void start(const char *section, quint32 address);
    void end(const char *section, quint32 address);

    char const *typeName() const { return "MemoryMapWriter"; }

    int size() const { return array.size(); }
    QByteArray data() const { return array; }
    void flush() { stream.flush(); }

private:
    QList<char const *> sectionStack;
    QByteArray array;
    QTextStream stream;

private:
    int level;
    void indent();
};

#endif // MEMORYMAPWRITER_H
