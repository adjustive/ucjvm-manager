#include "Struct_Method.h"

#include "JavaName.h"
#include "Method.h"
#include "NativeFunction.h"
#include "DataWriter.h"
#include "Struct_Exception_Handler_Table.h"
#include "Struct_CP_Table.h"

#include <QTextStream>

Struct_Method::Struct_Method(Method const &method)
    : exceptionHandlerTable(NULL)
    , offsetHandlers(0)
    , lengthHandlers(0)

    , exceptionsTable(NULL)
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

    , exceptionHandlers(method.exceptionHandlers())
    , exceptions(method.exceptions())

    , name(method.name())
    , descriptor(method.descriptor())
{
}

void Struct_Method::writeStruct(DataWriter &data) const
{
    if (!exceptionHandlers.isEmpty())
    {
        data.putAddress(exceptionHandlerTable, "exceptionHandlerTable");
        data.put16(offsetHandlers, "offsetHandlers");
        data.put16(lengthHandlers, "lengthHandlers");
    }
    else
    {
        data.putAddress(0, "exceptionHandlerTable");
        data.put16(0, "offsetHandlers");
        data.put16(0, "lengthHandlers");
    }

    if (!exceptions.isEmpty())
    {
        data.putAddress(exceptionsTable, "exceptionsTable");
        data.put16(offsetExceptions, "offsetExceptions");
        data.put16(lengthExceptions, "lengthExceptions");
    }
    else
    {
        data.putAddress(0, "exceptionsTable");
        data.put16(0, "offsetExceptions");
        data.put16(0, "lengthExceptions");
    }

    data.put16(accessFlags, "accessFlags");
    data.put16(nameIndex, "nameIndex");
    data.put16(descriptorIndex, "descriptorIndex");
    data.put16(maxStacks, "maxStacks");
    data.put16(maxLocals, "maxLocals");

    if (nativeFunction != NULL)
    {
        data.put16(nativeFunction->id, "nativeFunctionId");
    }
    else
    {
        data.put16(code.length(), "codeLength");
        data.putBytes(code, "code");
    }

    data.put8(parameterTypes.length(), "parameterTypesLength");
    data.putBytes(parameterTypes, "parameterTypes");
}

quint32 Struct_Method::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);
    return baseAddress;
}

void Struct_Method::printMemoryMap(QTextStream &ts) const
{
    ts << "      Method @0x" << structStart << " = {\n";
    ts << "        exception_handler = " << exceptionHandlerTable->structStart << "\n";
    ts << "        offset_handlers = " << offsetHandlers << "\n";
    ts << "        length_handlers = " << lengthHandlers << "\n";

    ts << "        exceptions = " << exceptionsTable->structStart << "\n";
    ts << "        offset_exceptions = " << offsetExceptions << "\n";
    ts << "        length_exceptions = " << lengthExceptions << "\n";

    ts << "        accessFlags = " << accessFlags << "\n";
    ts << "        nameIndex = " << nameIndex << "\n";
    ts << "        descriptorIndex = " << descriptorIndex << "\n";
    ts << "        maxStacks = " << maxStacks << "\n";
    ts << "        maxLocals = " << maxLocals << "\n";
    ts << "        codeLength = " << code.size() << "\n";

//    << descriptor << " " << name << "\n";
}


void Struct_Method::collectExceptions(Struct_Exception_Handler_Table &ehTable, Struct_Exceptions &eTable)
{
    exceptionHandlerTable = &ehTable;
    offsetHandlers = ehTable.size();
    lengthHandlers = exceptionHandlers.size();
    ehTable.add(exceptionHandlers);

    exceptionsTable = &eTable;
    offsetExceptions = eTable.size();
    lengthExceptions = exceptions.size();
    eTable.add(exceptions);
}

void Struct_Method::loadNativeInterface(QList<NativeFunction> const &nativeInterface, QString className, Struct_CP_Table const &constantPoolTable)
{
    if ((accessFlags & Method::ACC_NATIVE) == 0)
        return;

    QString name = constantPoolTable.getUtf8(nameIndex);
    QString descriptor = constantPoolTable.getUtf8(descriptorIndex);

    QString demangled = JavaName::demangle(descriptor, name, className);

    foreach (NativeFunction const &function, nativeInterface)
    {
        if (function.matches(className, name, descriptor))
        {
            if (nativeFunction != NULL)
                qWarning("duplicate native function %s: %d and %d",
                         demangled.toUtf8().constData(),
                         function.id, nativeFunction->id);
            else
                nativeFunction = &function;
        }
    }

    if (nativeFunction == NULL)
        qWarning("could not find native function for %s",
                 demangled.toUtf8().constData());
}
