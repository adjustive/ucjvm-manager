#include "Struct_Class.h"

#include "JVMClass.h"
#include "DataWriter.h"

Struct_Class::Struct_Class(const JVMClass &classData)
    : constantPoolTable(classData.constantPool())
    , fieldPoolTable(classData.fields())
    , methodPoolTable(classData.methods())

    , name(classData.name())
{
}

void Struct_Class::writeThis(DataWriter &data) const
{
    data.put32(constantPoolTable.memoryAddress);
    data.put32(fieldPoolTable.memoryAddress);
    data.put32(methodPoolTable.memoryAddress);

    data.put16(staticDataSize);
    data.put16(instanceDataSize);
    data.put16(staticDataHandle);
    data.put16(0);
}

void Struct_Class::writeChildren(DataWriter &data) const
{
    constantPoolTable.write(data);
    fieldPoolTable.write(data);
    methodPoolTable.write(data);
}
