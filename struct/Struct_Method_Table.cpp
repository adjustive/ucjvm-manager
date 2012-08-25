#include "Struct_Method_Table.h"

#include "Methods.h"
#include "DataWriter.h"

#include <QTextStream>

Struct_Method_Table::Struct_Method_Table(const Methods &methods)
{
    foreach (Method const &method, methods.methods())
        this->methods.append(Struct_Method(method));
}

void Struct_Method_Table::writeStruct(DataWriter &data) const
{
    data.put16(methods.size());
    data.pad16();

    foreach (Struct_Method const &method, methods)
        data.putAddress(method);
}

quint32 Struct_Method_Table::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);

    for (int i = 0; i < methods.size(); i++)
        baseAddress = methods[i].computeMemoryMap(baseAddress);

    return baseAddress;
}

void Struct_Method_Table::printMemoryMap(QTextStream &ts) const
{
    ts << "Method_Table @0x" << memoryAddress << " {\n";

    foreach (Struct_Method const &method, methods)
        method.printMemoryMap(ts);
    ts << "    }\n";
}
