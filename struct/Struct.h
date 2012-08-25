#ifndef STRUCT_H
#define STRUCT_H

#include <QtGlobal>

class DataWriter;
class QTextStream;

class Struct
{
public:
    Struct();
    virtual ~Struct();

    quint32 setMemoryAddress(quint32 baseAddress);
    quint32 memorySize() const;

    virtual void writeStruct(DataWriter &data) const = 0;
    virtual void writeData(DataWriter &data) const;
    void write(DataWriter &data) const;

    virtual quint32 computeMemoryMap(quint32 baseAddress) = 0;
    virtual void printMemoryMap(QTextStream &ts) const = 0;

public:
    quint32 memoryAddress;
};

#endif // STRUCT_H
