#ifndef STRUCT_EXCEPTION_HANDLER_H
#define STRUCT_EXCEPTION_HANDLER_H

#include "Struct.h"

class Struct_Exception_Handler : public Struct
{
public:
    Struct_Exception_Handler();

    void writeThis(DataWriter &data) const;

private:
    quint16 startPC;   // index into JVM_Method.code[]
    quint16 endPC;     // index into JVM_Method.code[]
    quint16 handlerPC; // index into JVM_Method.code[]
    quint16 catchType; // index into constant pool of type JVM_CP_Class
};

#endif // STRUCT_EXCEPTION_HANDLER_H
