#include "Struct_Method.h"

#include "Method.h"

Struct_Method::Struct_Method(Method const &method)
    : exceptionHandler()
    , offsetHandlers(0)
    , lengthHandlers(0)

    , exceptions()
    , offsetExceptions(0)
    , lengthExceptions(0)

    , accessFlags(method.accessFlags())
    , nameIndex(method.nameIndex())
    , descriptorIndex(method.descriptorIndex())
    , maxStacks(method.maxStack())
    , maxLocals(method.maxLocals())
    , code(method.code())
    , parameterTypes(method.parameters())
{
}

void Struct_Method::writeThis(DataWriter &data) const
{
}
