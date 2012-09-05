#include "Struct_Exception_Handler.h"

#include "ExceptionHandler.h"
#include "DataWriter.h"

Struct_Exception_Handler::Struct_Exception_Handler(ExceptionHandler const &handler)
    : startPC(handler.startPC())
    , endPC(handler.endPC())
    , handlerPC(handler.handlerPC())
    , catchType(handler.catchType())
{
}

void Struct_Exception_Handler::writeStruct(DataWriter &data) const
{
    data.put16(startPC, "startPC");
    data.put16(endPC, "endPC");
    data.put16(handlerPC, "handlerPC");
    data.put16(catchType, "catchType");
}

quint32 Struct_Exception_Handler::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);
    return baseAddress;
}

void Struct_Exception_Handler::printMemoryMap(QTextStream &ts) const
{
}
