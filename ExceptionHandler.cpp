#include "ExceptionHandler.h"

ExceptionHandler::ExceptionHandler(QDataStream &data)
{
    data >> d.startPC;
    data >> d.endPC;
    data >> d.handlerPC;
    data >> d.catchType;
}
