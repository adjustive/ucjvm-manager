#include "Fields.h"
#include "ConstantPool.h"
#include "Attributes.h"

Fields::Fields()
{
}

Fields::Fields(QDataStream &data, ConstantPool const &cp)
{
    quint16 count;
    data >> count;

    for (int i = 0; i < count; i++)
    {
        fields.append(Field(data, cp));
    }
}


quint16 Fields::count() const
{
    return fields.size();
}

Field const &Fields::get(int index) const
{
    return fields[index];
}
