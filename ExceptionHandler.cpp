#include "ExceptionHandler.h"

ExceptionHandler::ExceptionHandler(QDataStream &data)
{
    data >> d.startPC;
    data >> d.endPC;
    data >> d.handlerPC;
    data >> d.catchType;
}

quint16 ExceptionHandler::startPC() const
{
    return d.startPC;
}

quint16 ExceptionHandler::endPC() const
{
    return d.endPC;
}

quint16 ExceptionHandler::handlerPC() const
{
    return d.handlerPC;
}

quint16 ExceptionHandler::catchType() const
{
    return d.catchType;
}
