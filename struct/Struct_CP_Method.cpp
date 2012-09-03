#include "Struct_CP_Method.h"

#include "JavaName.h"
#include "Struct_CP_Name.h"
#include "Struct_Method.h"
#include "Struct_Class.h"
#include "ConstantPoolInfo_Methodref.h"
#include "DataWriter.h"
#include "ResolveContext.h"
#include "Struct_CP_Class.h"

#include <QTextStream>

Struct_CP_Method::Struct_CP_Method(const ConstantPoolInfo_Methodref &v)
    : classIndex(v.nameIndex())
    , descriptorIndex(v.descriptorIndex())
    , address(0)
    , realClass(0)
{
}

void Struct_CP_Method::resolveClassReferences(const ResolveContext &context)
{
    Struct_CP_Class &realClassInfo = context.constantTable().getClass(classIndex);
    realClassInfo.resolveClassReferences(context);
    realClass = realClassInfo.classAddress;
}

void Struct_CP_Method::resolveMethodReferences(const ResolveContext &context)
{
    Struct_CP_Name const &methodNameRef = context.constantTable().getName(descriptorIndex);

    QString methodName = context.constantTable().getUtf8(methodNameRef.nameIndex);
    QString methodDescriptor = context.constantTable().getUtf8(methodNameRef.descriptorIndex);

    Struct_Class const *current = realClass;
    do
    {
        Struct_Method const *method = current->methodPoolTable.getMethod(methodName, methodDescriptor);
        if (method != NULL)
            return;
    }
    while ((current = current->superClass()));

    qFatal("unable to resolve field %s %s in class %s",
           JavaName::demangle(methodDescriptor).toUtf8().constData(),
           methodName.toUtf8().constData(),
           realClass->javaTypeName().toUtf8().constData());
}

void Struct_CP_Method::writeStruct(DataWriter &data) const
{
    Struct_CP::writeStruct(data);
    data.put16(classIndex);
    data.put16(descriptorIndex);
    data.putAddress(address);
    data.putAddress(realClass);
}

quint32 Struct_CP_Method::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);
    return baseAddress;
}

void Struct_CP_Method::printMemoryMap(QTextStream &ts) const
{
    ts << "Method @0x" << structStart << " = " << classIndex << "(" << memoryAddress(realClass) << ")" << ", " << descriptorIndex << "(" << memoryAddress(address) << ")\n";
}
