#include "Struct_CP_Field.h"

#include "Struct_CP_Class.h"
#include "Struct_Field.h"
#include "Struct_Class.h"
#include "ConstantPoolInfo_Fieldref.h"
#include "DataWriter.h"
#include "ResolveContext.h"
#include "Struct_ClassTable.h"
#include "Struct_CP_Name.h"
#include "JavaName.h"

#include <QTextStream>

Struct_CP_Field::Struct_CP_Field(ConstantPoolInfo_Fieldref const &v)
    : classIndex(v.nameIndex())
    , descriptorIndex(v.descriptorIndex())
    , fieldAddress(0)
    , classAddress(0)
{
}

void Struct_CP_Field::resolveClassReferences(const ResolveContext &context)
{
    Struct_CP_Class &classInfo = context.constantTable().getClass(classIndex);
    classInfo.resolveClassReferences(context);
    classAddress = classInfo.classAddress;
}

void Struct_CP_Field::resolveFieldReferences(const ResolveContext &context)
{
    Struct_CP_Name const &fieldNameRef = context.constantTable().getName(descriptorIndex);

    QString fieldName = context.constantTable().getUtf8(fieldNameRef.nameIndex);
    QString fieldDescriptor = context.constantTable().getUtf8(fieldNameRef.descriptorIndex);

    Struct_Class const *current = classAddress;
    do
    {
        fieldAddress = current->fieldPoolTable.getField(fieldName, fieldDescriptor);
        if (fieldAddress != NULL)
            return;
    }
    while ((current = current->superClass()));

    qFatal("unable to resolve field %s %s in class %s",
           JavaName::demangle(fieldDescriptor).toUtf8().constData(),
           fieldName.toUtf8().constData(),
           classAddress->javaTypeName().toUtf8().constData());
}

void Struct_CP_Field::writeConstantData(DataWriter &data) const
{
    data.put16(classIndex, "classIndex");
    data.put16(descriptorIndex, "descriptorIndex");
    data.putAddress(fieldAddress, "fieldAddress");
    data.putAddress(classAddress, "classAddress");
}

quint32 Struct_CP_Field::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);
    return baseAddress;
}

void Struct_CP_Field::printMemoryMap(QTextStream &ts) const
{
    ts << "Field @0x" << structStart << " = " << classIndex << "(" << memoryAddress(classAddress) << ")" << ", " << descriptorIndex << "(" << memoryAddress(fieldAddress) << ")" << "\n";
}
