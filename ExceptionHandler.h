#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H

#include <QDataStream>

struct ExceptionHandlerPrivate
{
    quint16 startPC;
    quint16 endPC;
    quint16 handlerPC;
    quint16 catchType;
};

class ExceptionHandler
{
public:
    ExceptionHandler(QDataStream &data);

private:
    ExceptionHandlerPrivate d;
};

#endif // EXCEPTIONHANDLER_H
