#ifndef STRUCT_CP_DOUBLE_H
#define STRUCT_CP_DOUBLE_H

#include "Struct_CP.h"
class ConstantPoolInfo_Double;

class Struct_CP_Double : public Struct_CP
{
public:
    Struct_CP_Double(ConstantPoolInfo_Double const &v);

    void writeThis(DataWriter &data) const;

    Type type() const { return CONSTANT_TYPE_DOUBLE; }

public:
    double value;
};

#endif // STRUCT_CP_DOUBLE_H
