#ifndef STRUCT_CP_H
#define STRUCT_CP_H

#include "Struct.h"

class Struct_CP : public Struct
{
public:
    enum Type
    {
        CONSTANT_TYPE_UTF8                  = 1,
        CONSTANT_TYPE_INTEGER               = 3,
        CONSTANT_TYPE_FLOAT                 = 4,
        CONSTANT_TYPE_LONG                  = 5,
        CONSTANT_TYPE_DOUBLE                = 6,
        CONSTANT_TYPE_CLASS_INFO            = 7,
        CONSTANT_TYPE_STRING                = 8,
        CONSTANT_TYPE_FIELD_REF             = 9,
        CONSTANT_TYPE_METHOD_REF            = 10,
        CONSTANT_TYPE_INTERFACE_METHOD_REF  = 11,
        CONSTANT_TYPE_NAME_AND_TYPE         = 12
    };

public:
    Struct_CP();
    virtual ~Struct_CP();

    virtual Type type() const = 0;

    virtual void writeStruct(DataWriter &data) const = 0;
};

#endif // STRUCT_CP_H
