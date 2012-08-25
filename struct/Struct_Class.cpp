#include "Struct_Class.h"

#include "JVMClass.h"
#include "DataWriter.h"
#include "JavaName.h"

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

QString Struct_Class::name() const
{
    return className;
}

void Struct_Class::writeStruct(DataWriter &data) const
{
    data.put32(constantPoolTable.memoryAddress);
    data.put32(fieldPoolTable.memoryAddress);
    data.put32(methodPoolTable.memoryAddress);

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
}

quint32 Struct_Class::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);

    constantPoolTable.computeMemoryMap(baseAddress);
    fieldPoolTable.computeMemoryMap(baseAddress);
    methodPoolTable.computeMemoryMap(baseAddress);

    return baseAddress;
}

void Struct_Class::printMemoryMap(QTextStream &ts) const
{
    ts << "  Class " << JavaName::demangle(name()) << " @0x" << memoryAddress << " {\n";
#if 1
    ts << "    constantPoolTable = ";
    constantPoolTable.printMemoryMap(ts);
#endif
    ts << "    fieldPoolTable = ";
    fieldPoolTable.printMemoryMap(ts);
    ts << "    methodPoolTable = ";
    methodPoolTable.printMemoryMap(ts);
    ts << "    staticDataSize = " << staticDataSize << "\n";
    ts << "    instanceDataSize = " << instanceDataSize << "\n";
    ts << "    staticDataHandle = " << staticDataHandle << "\n";
    ts << "  }\n";
}
