#ifndef DATAWRITER_H
#define DATAWRITER_H

#include <QByteArray>
#include <QSharedPointer>

class Struct;

class DataWriter
{
    enum Size
    {
        BYTE_SIZE   = 1,
        BYTE_ALIGN  = 1,
        SHORT_SIZE  = 2,
        SHORT_ALIGN = 2,
        INT_SIZE    = 4,
        INT_ALIGN   = 4,
        LONG_SIZE   = 8,
        LONG_ALIGN  = 8,

        FLOAT_SIZE  = 4,
        FLOAT_ALIGN = 4,
        DOUBLE_SIZE = 8,
        DOUBLE_ALIGN= 8,

        ADDRESS_SIZE = INT_SIZE,
        ADDRESS_ALIGN = INT_ALIGN
    };

private:
    virtual bool permissive() const = 0;

    virtual void write8(quint8 value) = 0;
    virtual void write16(quint16 value) = 0;
    virtual void write32(quint32 value) = 0;
    virtual void write64(quint64 value) = 0;
    virtual void writeFloat(float value) = 0;
    virtual void writeDouble(double value) = 0;

    virtual void wrote(quint16 bytes);

    virtual void checkAlign(Size alignment) const;

public:
    DataWriter(quint32 baseAddress = 0);

    static quint32 align(quint32 address, quint8 alignment);
    void align(quint8 alignment);
    void verifyPosition(quint32 currentAddress, quint32 nextAddress);

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
    void putAddress(QSharedPointer<Struct> pointer);

    void pad8();
    void pad16();
    void pad32();
    void pad64();

    virtual char const *typeName() const = 0;

private:
    quint32 const baseAddress;
    quint32 nextAddress;
    quint32 currentAddress;
};

#endif // DATAWRITER_H
