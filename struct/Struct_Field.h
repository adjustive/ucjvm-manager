#ifndef STRUCT_FIELD_H
#define STRUCT_FIELD_H

#include "Struct.h"

class Field;

class Struct_Field : public Struct
{
public:
    Struct_Field(Field const &field);

    quint16 setDataOffset(quint16 base);

    bool isStatic() const;

    quint8 alignment() const { return 2; }
    void writeStruct(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    char const *typeName() const { return "Field"; }

private:
    quint16 accessFlags;
    quint16 dataOffset;
    quint16 constantValueReference;
    quint8 fieldType;

public:
    quint16 nameIndex;
    quint16 descriptorIndex;

    QString name;
    QString descriptor;

private:
    quint16 dataSize;
};

#endif // STRUCT_FIELD_H
