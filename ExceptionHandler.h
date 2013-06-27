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

    quint16 startPC() const;
    quint16 endPC() const;
    quint16 handlerPC() const;
    quint16 catchType() const;

private:
    ExceptionHandlerPrivate d;
};

#endif // EXCEPTIONHANDLER_H
