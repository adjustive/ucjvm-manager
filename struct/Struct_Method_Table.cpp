#include "Struct_Method_Table.h"

#include "Methods.h"

Struct_Method_Table::Struct_Method_Table(const Methods &methods)
{
    foreach (Method const &method, methods.methods())
    {
        this->methods.append(Struct_Method(method));
    }
}

void Struct_Method_Table::writeThis(DataWriter &data) const
{
}
