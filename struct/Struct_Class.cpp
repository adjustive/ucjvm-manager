#include "Struct_Class.h"

#include "Struct_CP_Class.h"
#include "JVMClass.h"
#include "DataWriter.h"
#include "JavaName.h"
#include "ResolveContext.h"

#include <QTextStream>

Struct_Class::Struct_Class(const JVMClass &classData)
    : constantPoolTable(classData.constantPool())
    , fieldPoolTable(classData.fields())
    , methodPoolTable(classData.methods())

    , staticDataSize(0)
    , instanceDataSize(0)
    , staticDataHandle(0)

    , className(classData.name())
{
}

QString Struct_Class::javaTypeName() const
{
    return className;
}

Struct_Class const *Struct_Class::superClass() const
{
    Struct_CP_Class const &superClassInfo = constantPoolTable.getClass(3);
    Struct_Class const *superClass = superClassInfo.classAddress;
    Q_ASSERT(superClass != NULL);
    if (superClass->javaTypeName() == "java/lang/Object")
        return NULL;
    return superClass;
}

void Struct_Class::collectExceptions()
{
    methodPoolTable.collectExceptions(exceptionHandlerTable, exceptionsTable);
}

void Struct_Class::loadNativeInterface(QList<NativeFunction> const &nativeInterface)
{
//    qDebug("loading native interface for %s", name().toUtf8().constData());
    methodPoolTable.loadNativeInterface(nativeInterface, javaTypeName(), constantPoolTable);
}

ResolveContext Struct_Class::resolveContext(ResolveContext const &context) const
{
    return context
        .setConstantTable(constantPoolTable)
        .setFieldTable(fieldPoolTable)
        .setMethodTable(methodPoolTable);
}

void Struct_Class::resolveClassReferences(ResolveContext const &context)
{
    constantPoolTable.resolveClassReferences(resolveContext(context));
}

void Struct_Class::resolveFieldReferences(const ResolveContext &context)
{
    constantPoolTable.resolveFieldReferences(resolveContext(context));
}

void Struct_Class::resolveMethodReferences(const ResolveContext &context)
{
    constantPoolTable.resolveMethodReferences(resolveContext(context));
}

void Struct_Class::writeStruct(DataWriter &data) const
{
    data.put32(constantPoolTable.structStart);
    data.put32(fieldPoolTable.structStart);
    data.put32(methodPoolTable.structStart);

    data.put16(staticDataSize);
    data.put16(instanceDataSize);
    data.put16(staticDataHandle);
    data.pad16();
}

void Struct_Class::writeData(DataWriter &data) const
{
    constantPoolTable.write(data);
    fieldPoolTable.write(data);
    methodPoolTable.write(data);

    exceptionHandlerTable.write(data);
    exceptionsTable.write(data);
}

quint32 Struct_Class::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);

    baseAddress = constantPoolTable.computeMemoryMap(baseAddress);
    baseAddress = fieldPoolTable.computeMemoryMap(baseAddress);
    baseAddress = methodPoolTable.computeMemoryMap(baseAddress);

    baseAddress = exceptionHandlerTable.computeMemoryMap(baseAddress);
    baseAddress = exceptionsTable.computeMemoryMap(baseAddress);

    return baseAddress;
}

void Struct_Class::printMemoryMap(QTextStream &ts) const
{
    ts << "  Class " << JavaName::demangle(javaTypeName()) << " @0x" << structStart << " {\n";
    ts << "    constantPoolTable = ";
    constantPoolTable.printMemoryMap(ts);
    ts << "    fieldPoolTable = ";
    fieldPoolTable.printMemoryMap(ts);
    ts << "    methodPoolTable = ";
    methodPoolTable.printMemoryMap(ts);
    ts << "    staticDataSize = " << staticDataSize << "\n";
    ts << "    instanceDataSize = " << instanceDataSize << "\n";
    ts << "    staticDataHandle = " << staticDataHandle << "\n";
    ts << "  }\n";
}
