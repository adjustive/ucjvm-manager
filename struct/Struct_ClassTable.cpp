#include "Struct_ClassTable.h"

#include "JVMClassList.h"

#include <QDebug>

Struct_ClassTable::Struct_ClassTable(JVMClassList const &classList, quint32 baseAddress)
{
    foreach (JVMClass const &classData, classList)
    {
        classes.append(Struct_Class(classData));
    }

    sort();
    computeClassPositions(baseAddress);
}


struct FindClass
{
    FindClass(QString name)
        : name(name)
    {
    }

    bool operator()(Struct_Class const &candidate) const
    {
        return candidate.name == name;
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


quint32 Struct_ClassTable::computeClassPositions(quint32 baseAddress)
{
    for (int i = 0; i < classes.size(); i++)
        baseAddress = classes[i].setMemoryAddress(baseAddress);
    return baseAddress;
}


void Struct_ClassTable::writeThis(DataWriter &data) const
{
}
