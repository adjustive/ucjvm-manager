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
    DataWriter(quint32 baseAddress);

    static quint32 align(quint32 address, quint8 alignment);
    void align(quint8 alignment);
    void verifyPosition(quint32 currentAddress, quint32 nextAddress);

    virtual quint32 memorySize() const;

    void put8(quint8 value, char const *field);
    void put16(quint16 value, char const *field);
    void put32(quint32 value, char const *field);
    void put64(quint64 value, char const *field);
    void putFloat(float value, char const *field);
    void putDouble(double value, char const *field);

    void putBytes(QByteArray value, char const *field);
    void putAddress(Struct const &reference, char const *field);
    void putAddress(Struct const *pointer, char const *field);
    void putAddress(QSharedPointer<Struct> pointer, char const *field);

    void pad8();
    void pad16();
    void pad32();
    void pad64();

    virtual void start(char const *section, quint32 address);
    virtual void end(char const *section, quint32 address);

    virtual char const *typeName() const = 0;

protected:
    quint32 const baseAddress;

private:
    quint32 nextAddress;
    quint32 currentAddress;
};

#endif // DATAWRITER_H
