#include "Attributes.h"
#include "ConstantPool.h"

#include <QDataStream>

Attributes::Attributes()
{
}

Attributes::Attributes(QDataStream &data, ConstantPool const &cp)
{
    quint16 count;
    data >> count;

    for (int i = 0; i < count; i++)
    {
        attributes.append(AttributesInfo::parse(data, cp));
    }
}
