#ifndef DATAWRITER_H
#define DATAWRITER_H

#include <QByteArray>

class DataWriter
{
public:
    DataWriter();

    virtual void put8(quint8 value) = 0;
    virtual void put16(quint16 value) = 0;
    virtual void put32(quint32 value) = 0;
    virtual void put64(quint64 value) = 0;
    virtual void put(QByteArray value) = 0;
};

#endif // DATAWRITER_H
