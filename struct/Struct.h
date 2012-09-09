#ifndef STRUCT_H
#define STRUCT_H

#include <QPair>

#include "MemoryModel.h"
class ResolveContext;
class DataWriter;
class QTextStream;

class Struct
{
protected:
    static quint32 memoryAddress(Struct const *pointer);

public:
    Struct();
    virtual ~Struct();

    quint32 setMemoryAddress(const MemoryModel &memoryModel, quint32 baseAddress);
private:
    QPair<quint32, quint32> computeMemorySize(const MemoryModel &memoryModel, quint32 baseAddress) const;

public:
    virtual MemoryModel::Align alignment() const = 0;
    virtual void writeStruct(DataWriter &data) const = 0;
    virtual void writeData(DataWriter &data) const;
    void write(DataWriter &data) const;

    virtual void resolveClassReferences(ResolveContext const &context) { Q_UNUSED(context); }
    virtual void resolveFieldReferences(ResolveContext const &context) { Q_UNUSED(context); }
    virtual void resolveMethodReferences(ResolveContext const &context) { Q_UNUSED(context); }

    virtual quint32 computeMemoryMap(MemoryModel const &memoryModel, quint32 baseAddress) = 0;
    virtual void printMemoryMap(QTextStream &ts) const = 0;

    virtual char const *typeName() const = 0;

public:
    quint32 structStart;
    quint32 dataStart;
    quint32 dataEnd;
};

#endif // STRUCT_H
