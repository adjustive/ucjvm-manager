#include "Struct_Method.h"

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
    data.putAddress(0);
//    data.putAddress(exceptionHandlerTable);
    data.put16(offsetHandlers);
    data.put16(lengthHandlers);

    data.putAddress(0);
//    data.putAddress(exceptionsTable);
    data.put16(offsetExceptions);
    data.put16(lengthExceptions);

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
        data.putBytes(code);
    }

    data.put8(parameterTypes.length());
    data.putBytes(parameterTypes);
}

quint32 Struct_Method::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);
    return baseAddress;
}

void Struct_Method::printMemoryMap(QTextStream &ts) const
{
    ts << "      Method @0x" << structStart << " = " << descriptor << " " << name << "\n";
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

    foreach (NativeFunction const &function, nativeInterface)
    {
        if (function.matches(className, name, descriptor))
        {
            if (nativeFunction != NULL)
                qWarning("duplicate native function %s%s: %d and %d",
                         name.toUtf8().constData(), descriptor.toUtf8().constData(),
                         function.id, nativeFunction->id);
            else
                nativeFunction = &function;
        }
    }

    if (nativeFunction == NULL)
        qWarning("could not find native function for %s%s", name.toUtf8().constData(), descriptor.toUtf8().constData());
}
