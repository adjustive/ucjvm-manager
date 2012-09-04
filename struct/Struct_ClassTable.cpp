#include "Struct_ClassTable.h"

#include "JVMClassList.h"
#include "DataWriter.h"
#include "ResolveContext.h"

#include <QDebug>

Struct_ClassTable::Struct_ClassTable(JVMClassList const &classList, quint32 baseAddress, QList<NativeFunction> const &nativeInterface)
{
    foreach (JVMClass const &classData, classList)
        classes.append(Struct_Class(classData));

    for (int i = 0; i < classes.size(); i++)
        classes[i].collectExceptions();

    sort();
    loadNativeInterface(nativeInterface);
    resolveClassReferences();
    computeMemoryMap(baseAddress);
}


Struct_Class const &Struct_ClassTable::byName(QString name) const
{
    foreach (Struct_Class const &classData, classes)
        if (classData.javaTypeName() == name)
            return classData;

    throw "not found";
}


struct FindClass
{
    FindClass(QString name)
        : name(name)
    {
    }

    bool operator()(Struct_Class const &candidate) const
    {
        return candidate.javaTypeName() == name;
    }

private:
    QString const name;
};

void Struct_ClassTable::moveClass(QString name, int index)
{
    QList<Struct_Class>::iterator found = std::find_if(classes.begin(), classes.end(), FindClass(name));
    if (found == classes.end())
    {
        qWarning() << "could not find class" << name;
        return;
    }

    qSwap(classes[index], *found);
}

void Struct_ClassTable::sort()
{
    static struct
    {
        char const *className;
        int position;
    } fixedOrder[] = {
        { "java/lang/Object", 0 },
		{ "java/lang/String", 1 },

        // exceptions
		{ "java/lang/Throwable", 2 },
		{ "java/lang/Exception", 3 },
		{ "java/lang/NullPointerException", 4 },
		{ "java/lang/ArithmeticException", 5 },
		{ "java/lang/NegativeArraySizeException", 6 },
		{ "java/lang/IndexOutOfBoundsException", 7 },
		{ "java/lang/ArrayIndexOutOfBoundsException", 8 },
//	    { "java/lang/IllegalFunctionCallException", 9 },
		{ "java/lang/Error", 10 },
		{ "java/lang/LinkageError", 10 },
		{ "java/lang/UnsatisfiedLinkError", 11 },
    };

    for (size_t i = 0; i < sizeof fixedOrder / sizeof *fixedOrder; i++)
        moveClass(fixedOrder[i].className, fixedOrder[i].position);
}


void Struct_ClassTable::loadNativeInterface(QList<NativeFunction> const &nativeInterface)
{
    for (int i = 0; i < classes.size(); i++)
        classes[i].loadNativeInterface(nativeInterface);
}


void Struct_ClassTable::resolveClassReferences()
{
    ResolveContext context = ResolveContext().setClassTable(*this);
    for (int i = 0; i < classes.size(); i++)
        classes[i].resolveClassReferences(context);
    for (int i = 0; i < classes.size(); i++)
        classes[i].resolveFieldReferences(context);
    for (int i = 0; i < classes.size(); i++)
        classes[i].resolveMethodReferences(context);
}


void Struct_ClassTable::writeStruct(DataWriter &data) const
{
    data.put16(classes.size());
    data.pad16();

    data.putAddress(/*resource table address*/0);
//    data.putBytes("RTBL");

    foreach (Struct_Class const &classData, classes)
        data.put32(classData.structStart);
}

void Struct_ClassTable::writeData(DataWriter &data) const
{
    foreach (Struct_Class const &classData, classes)
        classData.write(data);
}


quint32 Struct_ClassTable::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);

    for (int i = 0; i < classes.size(); i++)
        baseAddress = classes[i].computeMemoryMap(baseAddress);

    return baseAddress;
}


void Struct_ClassTable::printMemoryMap(QTextStream &ts) const
{
    ts << "ClassTable @0x" << hex << structStart << " {\n";

    foreach (Struct_Class const &classData, classes)
        classData.printMemoryMap(ts);

    ts << "}\n";
}
