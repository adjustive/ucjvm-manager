#include "Struct_Method.h"

#include "Method.h"
#include "NativeFunction.h"
#include "DataWriter.h"

#include <QTextStream>

Struct_Method::Struct_Method(Method const &method)
    : exceptionHandler(NULL)
    , offsetHandlers(0)
    , lengthHandlers(0)

    , exceptions(NULL)
    , offsetExceptions(0)
    , lengthExceptions(0)

    , accessFlags(method.accessFlags())
    , nameIndex(method.nameIndex())
    , descriptorIndex(method.descriptorIndex())
    , maxStacks(method.maxStack())
    , maxLocals(method.maxLocals())
    , nativeFunction(NULL)
    , code(method.code())
    , parameterTypes(method.parameters())
{
}

void Struct_Method::writeStruct(DataWriter &data) const
{
    // TODO: exceptions
    data.putAddress(0);
    data.put16(0);
    data.put16(0);

    data.putAddress(0);
    data.put16(0);
    data.put16(0);

    data.put16(accessFlags);
    data.put16(nameIndex);
    data.put16(descriptorIndex);
    data.put16(maxStacks);
    data.put16(maxLocals);

    if (nativeFunction != NULL)
    {
        data.put16(nativeFunction->id);
    }
    else
    {
        data.put16(code.length());
        data.put(code);
    }

    data.put16(parameterTypes.length());
    data.put(parameterTypes);
}

quint32 Struct_Method::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);
    return baseAddress;
}

void Struct_Method::printMemoryMap(QTextStream &ts) const
{
    ts << "      Method @0x" << memoryAddress << " { nameIndex = " << nameIndex << " }\n";
}
