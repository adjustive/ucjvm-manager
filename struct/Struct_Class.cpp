#include "Struct_Class.h"

#include "Struct_CP_Class.h"
#include "Class.h"
#include "DataWriter.h"
#include "JavaName.h"
#include "ResolveContext.h"

#include <QTextStream>

Struct_Class::Struct_Class(const Class &classData)
    : constantPoolTable(classData.constantPool())
    , fieldPoolTable(classData.fields())
    , methodPoolTable(classData.methods())

    , inheritedStaticDataSize(0)
    , inheritedInstanceDataSize(0)
    , staticDataHandle(0)

    , ownStaticDataSize(classData.staticDataSize())
    , ownInstanceDataSize(classData.instanceDataSize())

    , className(classData.name())
{
}

QString Struct_Class::javaTypeName() const
{
    return className;
}

Struct_Class const *Struct_Class::superClass() const
{
    if (javaTypeName() == "java/lang/Object")
        return NULL;

    Struct_CP_Class const &superClassInfo = constantPoolTable.getClass(3);
    Struct_Class const *superClass = superClassInfo.classAddress;
    Q_ASSERT(superClass != NULL);
    return superClass;
}

void Struct_Class::collectExceptions()
{
    methodPoolTable.collectExceptions(exceptionHandlerTable, exceptionsTable);
}

void Struct_Class::setStaticDataHandle(quint16 staticDataHandle)
{
    this->staticDataHandle = staticDataHandle;
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


void Struct_Class::computeDataSize()
{
    Struct_Class const *current = this;

    inheritedStaticDataSize = 0;
    inheritedInstanceDataSize = 0;

    while ((current = current->superClass()))
    {
        inheritedStaticDataSize += current->ownStaticDataSize;
        inheritedInstanceDataSize += current->ownInstanceDataSize;
    }
}


void Struct_Class::computeFieldOffsets()
{
    fieldPoolTable.computeFieldOffsets(inheritedStaticDataSize, inheritedInstanceDataSize);
}


void Struct_Class::writeStruct(DataWriter &data) const
{
    data.put32(constantPoolTable.structStart, "constantPoolTable");
    data.put32(fieldPoolTable.structStart, "fieldPoolTable");
    data.put32(methodPoolTable.structStart, "methodPoolTable");

    data.put16(inheritedStaticDataSize + ownStaticDataSize, "staticDataSize");
    data.put16(inheritedInstanceDataSize + ownInstanceDataSize, "instanceDataSize");
    data.put16(staticDataHandle, "staticDataHandle");
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
    ts << "    staticDataSize = " << inheritedStaticDataSize + ownStaticDataSize << "\n";
    ts << "    instanceDataSize = " << inheritedInstanceDataSize + ownInstanceDataSize << "\n";
    ts << "    staticDataHandle = " << staticDataHandle << "\n";
    ts << "  }\n";
}
