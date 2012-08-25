#ifndef DATAWRITER_H
#define DATAWRITER_H

#include <QByteArray>

class Struct;

class DataWriter
{
private:
    virtual bool nullOk() const = 0;

    virtual void write8(quint8 value) = 0;
    virtual void write16(quint16 value) = 0;
    virtual void write32(quint32 value) = 0;
    virtual void write64(quint64 value) = 0;
    virtual void writeFloat(float value) = 0;
    virtual void writeDouble(double value) = 0;

    virtual void wrote(int bytes);

    virtual void checkAlign(int alignment) const;
    void setAlign(int alignment);

public:
    DataWriter();

    void align8();
    void align16();
    void align32();
    void align64();
    void alignFloat();
    void alignDouble();
    void alignAddress();

    virtual quint32 memorySize() const;

    void put8(quint8 value);
    void put16(quint16 value);
    void put32(quint32 value);
    void put64(quint64 value);
    void putFloat(float value);
    void putDouble(double value);

    void putBytes(QByteArray value);
    void putAddress(Struct const &reference);
    void putAddress(Struct const *pointer);

    void pad8();
    void pad16();
    void pad32();
    void pad64();

    virtual char const *name() const = 0;

private:
    quint32 written;
};

#endif // DATAWRITER_H
