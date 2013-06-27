#include "ExceptionHandlers.h"

#include <QDataStream>

ExceptionHandlers::ExceptionHandlers()
{
}

ExceptionHandlers::ExceptionHandlers(QDataStream &data)
{
    quint16 count;
    data >> count;

    for (int i = 0; i < count; i++)
        d.handlers.append(ExceptionHandler(data));

    Q_ASSERT(d.handlers.size() == count);
}

QList<ExceptionHandler> ExceptionHandlers::handlers() const
{
    return d.handlers;
}
