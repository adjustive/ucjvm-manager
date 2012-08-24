#ifndef STRUCT_CP_STRING_H
#define STRUCT_CP_STRING_H

#include "Struct_CP.h"
class ConstantPoolInfo_String;

class Struct_CP_String : public Struct_CP
{
public:
    Struct_CP_String(ConstantPoolInfo_String const &v);

    void writeThis(DataWriter &data) const;

    Type type() const { return CONSTANT_TYPE_STRING; }

public:
    quint16 stringIndex;
};

#endif // STRUCT_CP_STRING_H
