#include "MemoryModel.h"


struct MemoryModelPrivate
{
    quint8 int8_size;
    quint8 int8_align;
    quint8 int16_size;
    quint8 int16_align;
    quint8 int32_size;
    quint8 int32_align;
    quint8 int64_size;
    quint8 int64_align;

    quint8 float_size;
    quint8 float_align;
    quint8 double_size;
    quint8 double_align;

    quint8 address_size;
    quint8 address_align;

    MemoryModel::ByteOrder byte_order;
};

MemoryModelPrivate AVR32_d = {
    1, 1, 2, 2, 4, 4, 8, 4,
    4, 4, 8, 8,
    4, 4,

    MemoryModel::BigEndian
};
MemoryModel const MemoryModel::AVR32(AVR32_d);

MemoryModelPrivate I386_d = {
    1, 1, 2, 2, 4, 4, 8, 4,
    4, 4, 8, 8,
    4, 4,

    MemoryModel::LittleEndian
};
MemoryModel const MemoryModel::I386(I386_d);

MemoryModelPrivate AMD64_d = {
    1, 1, 2, 2, 4, 4, 8, 8,
    4, 4, 8, 8,
    8, 8,

    MemoryModel::LittleEndian
};
MemoryModel const MemoryModel::AMD64(AMD64_d);



MemoryModel::MemoryModel(const MemoryModelPrivate &d)
    : d(d)
{
}


quint8 MemoryModel::sizeInBytes(Size size) const
{
    switch (size.value)
    {
    case INT8_SIZE:     return d.int8_size;
    case INT16_SIZE:    return d.int16_size;
    case INT32_SIZE:    return d.int32_size;
    case INT64_SIZE:    return d.int64_size;

    case FLOAT_SIZE:    return d.float_size;
    case DOUBLE_SIZE:   return d.double_size;

    case ADDRESS_SIZE:  return d.address_size;
    }

    qFatal("invalid case: %d", size.value);
    return 0;
}

quint8 MemoryModel::alignmentInBytes(Align align) const
{
    switch (align.value)
    {
    case INT8_ALIGN:    return d.int8_align;
    case INT16_ALIGN:   return d.int16_align;
    case INT32_ALIGN:   return d.int32_align;
    case INT64_ALIGN:   return d.int64_align;

    case FLOAT_ALIGN:   return d.float_align;
    case DOUBLE_ALIGN:  return d.double_align;

    case ADDRESS_ALIGN: return d.address_align;
    }

    qFatal("invalid case: %d", align.value);
    return 0;
}


MemoryModel::ByteOrder MemoryModel::byteOrder() const
{
    return d.byte_order;
}
