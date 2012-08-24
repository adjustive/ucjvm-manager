#ifndef STRUCT_H
#define STRUCT_H

#include <QtGlobal>

class DataWriter;

class Struct
{
public:
    Struct();
    virtual ~Struct();

    quint32 setMemoryAddress(quint32 baseAddress);
    quint32 memorySize() const;

    virtual void writeThis(DataWriter &data) const = 0;
    virtual void writeChildren(DataWriter &data) const;
    void write(DataWriter &data) const;

public:
    quint32 memoryAddress;
};

#endif // STRUCT_H
