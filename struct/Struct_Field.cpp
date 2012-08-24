#include "Struct_Field.h"

#include "Field.h"

Struct_Field::Struct_Field(Field const &field)
    : accessFlags(field.accessFlags())
    , dataOffset(0)
    , constantValueReference(field.constantValueIndex())
    , fieldType(field.dataType())
{
}

void Struct_Field::writeThis(DataWriter &data) const
{
}
