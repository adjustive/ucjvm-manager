#include "Struct_ClassTable.h"

#include "JVMClassList.h"
#include "DataWriter.h"

#include <QDebug>

Struct_ClassTable::Struct_ClassTable(JVMClassList const &classList, quint32 baseAddress, QList<NativeFunction> const &nativeInterface)
{
    foreach (JVMClass const &classData, classList)
        classes.append(Struct_Class(classData));

    sort();
    loadNativeInterface(nativeInterface);
    computeMemoryMap(baseAddress);
}


struct FindClass
{
    FindClass(QString name)
        : name(name)
    {
    }

    bool operator()(Struct_Class const &candidate) const
    {
        return candidate.name() == name;
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
    moveClass("java/lang/Object", 0);
    moveClass("java/lang/String", 1);

    // exceptions
    moveClass("java/lang/Throwable", 2);
    moveClass("java/lang/Exception", 3);
    moveClass("java/lang/NullPointerException", 4);
    moveClass("java/lang/ArithmeticException", 5);
    moveClass("java/lang/NegativeArraySizeException", 6);
    moveClass("java/lang/IndexOutOfBoundsException", 7);
    moveClass("java/lang/ArrayIndexOutOfBoundsException", 8);
//	moveClass("java/lang/IllegalFunctionCallException", 9);
    moveClass("java/lang/Error", 10);
    moveClass("java/lang/LinkageError", 10);
    moveClass("java/lang/UnsatisfiedLinkError", 11);
}


void Struct_ClassTable::loadNativeInterface(QList<NativeFunction> const &nativeInterface)
{
    for (int i = 0; i < classes.size(); i++)
        classes[i].loadNativeInterface(nativeInterface);
}


void Struct_ClassTable::writeStruct(DataWriter &data) const
{
    data.put16(classes.size());
    data.pad16();

    data.putAddress(/*resource table address*/0);

    foreach (Struct_Class const &classData, classes)
        data.put32(classData.memoryAddress);
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
    ts << "ClassTable @0x" << hex << memoryAddress << " {\n";

    foreach (Struct_Class const &classData, classes)
        classData.printMemoryMap(ts);

    ts << "}\n";
}
