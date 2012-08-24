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
        d.fields.append(Field(data, cp));
    }
}


quint16 Fields::count() const
{
    return d.fields.size();
}

Field const &Fields::get(int index) const
{
    return d.fields[index];
}

QList<Field> Fields::fields() const
{
    return d.fields;
}
