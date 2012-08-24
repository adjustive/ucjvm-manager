#ifndef STRUCT_CP_LONG_H
#define STRUCT_CP_LONG_H

#include "Struct_CP.h"
class ConstantPoolInfo_Long;

class Struct_CP_Long : public Struct_CP
{
public:
    Struct_CP_Long(ConstantPoolInfo_Long const &v);

    void writeThis(DataWriter &data) const;

    Type type() const { return CONSTANT_TYPE_LONG; }

public:
    quint64 value;
};

#endif // STRUCT_CP_LONG_H
