#ifndef STRUCT_CP_FLOAT_H
#define STRUCT_CP_FLOAT_H

#include "Struct_CP.h"
class ConstantPoolInfo_Float;

class Struct_CP_Float : public Struct_CP
{
public:
    Struct_CP_Float(ConstantPoolInfo_Float const &v);

    void writeThis(DataWriter &data) const;

    Type type() const { return CONSTANT_TYPE_FLOAT; }

public:
    float value;
};

#endif // STRUCT_CP_FLOAT_H
