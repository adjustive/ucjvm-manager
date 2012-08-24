#include "AttributesInfo_Exceptions.h"

#include <QDataStream>

AttributesInfo_Exceptions::AttributesInfo_Exceptions(QDataStream &data)
{
    quint16 count;
    data >> count;

    for (int i = 0; i < count; i++)
    {
        quint16 handler;
        data >> handler;

        d.exceptionTable.append(handler);
    }

    Q_ASSERT(d.exceptionTable.size() == count);
}

QList<quint16> AttributesInfo_Exceptions::exceptions() const
{
    return d.exceptionTable;
}
