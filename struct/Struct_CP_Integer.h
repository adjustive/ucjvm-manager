#ifndef STRUCT_CP_INTEGER_H
#define STRUCT_CP_INTEGER_H

#include "Struct_CP.h"
class ConstantPoolInfo_Integer;

class Struct_CP_Integer : public Struct_CP
{
public:
    Struct_CP_Integer(ConstantPoolInfo_Integer const &v);

    void writeStruct(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    Type type() const { return CONSTANT_TYPE_INTEGER; }

private:
    quint32 value;
};

#endif // STRUCT_CP_INTEGER_H
