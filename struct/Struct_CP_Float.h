#ifndef STRUCT_CP_FLOAT_H
#define STRUCT_CP_FLOAT_H

#include "Struct_CP.h"
class ConstantPoolInfo_Float;

class Struct_CP_Float : public Struct_CP
{
public:
    Struct_CP_Float(ConstantPoolInfo_Float const &v);

    void writeStruct(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    Type type() const { return CONSTANT_TYPE_FLOAT; }

private:
    float value;
};

#endif // STRUCT_CP_FLOAT_H
