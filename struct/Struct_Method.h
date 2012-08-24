#ifndef STRUCT_METHOD_H
#define STRUCT_METHOD_H

#include "Struct_Exception_Handler.h"
#include "Struct_Exceptions.h"
class Method;

#include <QByteArray>

class Struct_Method : public Struct
{
public:
    Struct_Method(Method const &method);

    void writeThis(DataWriter &data) const;

private:
    Struct_Exception_Handler exceptionHandler;
    quint16 offsetHandlers; // offset from exception handler address
    quint16 lengthHandlers; // total count of exception handlers

    Struct_Exceptions exceptions;
    quint16 offsetExceptions; // offset from exceptions address
    quint16 lengthExceptions; // total count of exceptions

    quint16 accessFlags;
    quint16 nameIndex;
    quint16 descriptorIndex;
    quint16 maxStacks;
    quint16 maxLocals;

    QByteArray code;
    QByteArray parameterTypes;
};

#endif // STRUCT_METHOD_H
