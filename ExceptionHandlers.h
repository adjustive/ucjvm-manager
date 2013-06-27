#ifndef EXCEPTIONHANDLERS_H
#define EXCEPTIONHANDLERS_H

#include <QList>

#include "ExceptionHandler.h"

struct ExceptionHandlersPrivate
{
    QList<ExceptionHandler> handlers;
};

class ExceptionHandlers
{
public:
    ExceptionHandlers();
    ExceptionHandlers(QDataStream &data);

    QList<ExceptionHandler> handlers() const;

private:
    ExceptionHandlersPrivate d;
};

#endif // EXCEPTIONHANDLERS_H
