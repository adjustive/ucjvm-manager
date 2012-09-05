#include "Struct_Method_Table.h"

#include "JavaName.h"
#include "Methods.h"
#include "DataWriter.h"

#include <QTextStream>

Struct_Method_Table::Struct_Method_Table(const Methods &methods)
{
    foreach (Method const &method, methods.methods())
        this->methods.append(Struct_Method(method));
}

Struct_Method const *Struct_Method_Table::getMethod(QString name, QString descriptor) const
{
#if 0
    qDebug("resolving field: %s %s",
           JavaName::demangle(descriptor).toUtf8().constData(),
           name.toUtf8().constData());
#endif
    foreach (Struct_Method const &method, methods)
        if (method.name == name && method.descriptor == descriptor)
        {
#if 0
            qDebug("method resolved: %s %s (%p)",
                   JavaName::demangle(descriptor).toUtf8().constData(),
                   name.toUtf8().constData(),
                   &method);
#endif
            return &method;
        }

    return NULL;
}

void Struct_Method_Table::writeStruct(DataWriter &data) const
{
    data.put16(methods.size(), "size");
    data.pad16();

    foreach (Struct_Method const &method, methods)
        data.putAddress(method, "method");
}

void Struct_Method_Table::writeData(DataWriter &data) const
{
    foreach (Struct_Method const &method, methods)
        method.write(data);
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
    ts << "Method_Table @0x" << structStart << " {\n";

    foreach (Struct_Method const &method, methods)
        method.printMemoryMap(ts);
    ts << "    }\n";
}


void Struct_Method_Table::collectExceptions(Struct_Exception_Handler_Table &ehTable, Struct_Exceptions &eTable)
{
    for (int i = 0; i < methods.size(); i++)
        methods[i].collectExceptions(ehTable, eTable);
}

void Struct_Method_Table::loadNativeInterface(QList<NativeFunction> const &nativeInterface, QString className, Struct_CP_Table const &constantPoolTable)
{
    for (int i = 0; i < methods.size(); i++)
        methods[i].loadNativeInterface(nativeInterface, className, constantPoolTable);
}
