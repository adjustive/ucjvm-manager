#include "Struct_Field_Table.h"

#include "Struct_Field.h"
#include "Fields.h"

Struct_Field_Table::Struct_Field_Table(Fields const &fields)
{
    foreach (Field const &field, fields.fields())
    {
        this->fields.append(Struct_Field(field));
    }
}

void Struct_Field_Table::writeThis(DataWriter &data) const
{
}
