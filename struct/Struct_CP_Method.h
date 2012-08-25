#ifndef STRUCT_CP_METHOD_H
#define STRUCT_CP_METHOD_H

#include "Struct_CP.h"
class Struct_Method;
class Struct_Class;
class ConstantPoolInfo_Methodref;

class Struct_CP_Method : public Struct_CP
{
public:
    Struct_CP_Method(ConstantPoolInfo_Methodref const &v);

    void writeStruct(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    Type type() const { return CONSTANT_TYPE_METHOD_REF; }

private:
    quint16 classIndex;
    quint16 descriptorIndex;
    Struct_Method *address;
    Struct_Class *realClass;
};

#endif // STRUCT_CP_METHOD_H
