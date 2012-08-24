#include "Interfaces.h"

#include <QDataStream>

Interfaces::Info::Info()
{
}

Interfaces::Info::Info(QDataStream &data)
{
    data >> nameIndex;
}


Interfaces::Interfaces()
{
}

Interfaces::Interfaces(QDataStream &data)
{
    quint16 count;
    data >> count;

    interfaces.reserve(count);

    for (int i = 0; i < count; i++)
    {
        interfaces.append(Info(data));
    }
}


quint16 Interfaces::count() const
{
    return interfaces.size();
}
