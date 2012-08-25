#ifndef STRUCT_FIELD_H
#define STRUCT_FIELD_H

#include "Struct.h"

class Field;

class Struct_Field : public Struct
{
public:
    Struct_Field(Field const &field);

    void writeStruct(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

private:
    quint16 accessFlags;
    quint16 dataOffset;
    quint16 constantValueReference;
    quint8 fieldType;
};

#endif // STRUCT_FIELD_H
