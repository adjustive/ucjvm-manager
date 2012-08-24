#ifndef STRUCT_CP_CLASS_H
#define STRUCT_CP_CLASS_H

#include "Struct_CP.h"
class Struct_Class;
class ConstantPoolInfo_Class;

class Struct_CP_Class : public Struct_CP
{
public:
    Struct_CP_Class(const ConstantPoolInfo_Class &v);

    void writeThis(DataWriter &data) const;

    Type type() const { return CONSTANT_TYPE_CLASS_INFO; }

public:
    quint16 index;
    Struct_Class *classAddress;
};

#endif // STRUCT_CP_CLASS_H
