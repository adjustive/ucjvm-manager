#ifndef MEMORYMODEL_H
#define MEMORYMODEL_H

#include <QtGlobal>

template<typename T>
struct Enum
{
    Enum(T value)
        : value(value)
    {
    }

    T value;
};

struct MemoryModelPrivate;

class MemoryModel
{
public:
    enum SizeType
    {
        INT8_SIZE,
        INT16_SIZE,
        INT32_SIZE,
        INT64_SIZE,

        FLOAT_SIZE,
        DOUBLE_SIZE,

        ADDRESS_SIZE
    };
    typedef Enum<SizeType> Size;

    enum AlignType
    {
        INT8_ALIGN,
        INT16_ALIGN,
        INT32_ALIGN,
        INT64_ALIGN,

        FLOAT_ALIGN,
        DOUBLE_ALIGN,

        ADDRESS_ALIGN
    };
    typedef Enum<AlignType> Align;

    enum ByteOrder
    {
        LittleEndian = 0x4321,
        BigEndian = 0x1234
    };

public:
    MemoryModel(MemoryModelPrivate const &d);

    quint8 sizeInBytes(Size size) const;
    quint8 alignmentInBytes(Align align) const;
    MemoryModel::ByteOrder byteOrder() const;

    static MemoryModel const AVR32;
    static MemoryModel const I386;
    static MemoryModel const AMD64;

private:
    MemoryModelPrivate const &d;
};

#endif // MEMORYMODEL_H
