#ifndef DATAWRITER_H
#define DATAWRITER_H

#include <QByteArray>

class Struct;

class DataWriter
{
private:
    virtual bool nullOk() const = 0;

public:
    DataWriter();

    virtual void put8(quint8 value) = 0;
    virtual void put16(quint16 value) = 0;
    virtual void put32(quint32 value) = 0;
    virtual void put64(quint64 value) = 0;
    virtual void putFloat(float value) = 0;
    virtual void putDouble(double value) = 0;

    void put(QByteArray value);
    void putAddress(Struct const &reference);
    void putAddress(Struct const *pointer);

    void pad8();
    void pad16();
    void pad32();
    void pad64();
};

#endif // DATAWRITER_H
