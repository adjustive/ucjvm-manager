#ifndef STRUCT_EXCEPTION_HANDLER_H
#define STRUCT_EXCEPTION_HANDLER_H

#include "Struct.h"
class ExceptionHandler;

class Struct_Exception_Handler : public Struct
{
public:
    Struct_Exception_Handler(ExceptionHandler const &handler);

    quint8 alignment() const { return 2; }
    void writeStruct(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    char const *typeName() const { return "Exception_Handler"; }

private:
    quint16 startPC;   // index into JVM_Method.code[]
    quint16 endPC;     // index into JVM_Method.code[]
    quint16 handlerPC; // index into JVM_Method.code[]
    quint16 catchType; // index into constant pool of type JVM_CP_Class
};

#endif // STRUCT_EXCEPTION_HANDLER_H
