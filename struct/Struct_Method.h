#ifndef STRUCT_METHOD_H
#define STRUCT_METHOD_H

#include "Struct_Exception_Handler.h"
#include "Struct_Exceptions.h"
#include "ExceptionHandler.h"
class Struct_Exception_Handler_Table;
class Method;
class NativeFunction;
class Struct_CP_Table;

#include <QByteArray>

class Struct_Method : public Struct
{
public:
    Struct_Method(Method const &method);

    void writeStruct(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    void collectExceptions(Struct_Exception_Handler_Table &ehTable, Struct_Exceptions &eTable);
    void loadNativeInterface(const QList<NativeFunction> &nativeInterface, QString className, const Struct_CP_Table &constantPoolTable);

private:
    Struct_Exception_Handler_Table *exceptionHandlerTable;
    quint16 offsetHandlers; // offset from exception handler address
    quint16 lengthHandlers; // total count of exception handlers

    Struct_Exceptions *exceptionsTable;
    quint16 offsetExceptions; // offset from exceptions address
    quint16 lengthExceptions; // total count of exceptions

    quint16 accessFlags;
    quint16 nameIndex;
    quint16 descriptorIndex;
    quint16 maxStacks;
    quint16 maxLocals;

    NativeFunction const *nativeFunction;
    QByteArray code;
    QByteArray parameterTypes;

private:
    QList<ExceptionHandler> exceptionHandlers;
    QList<quint16> exceptions;
};

#endif // STRUCT_METHOD_H
