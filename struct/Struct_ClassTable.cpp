#include "Struct_ClassTable.h"

#include "ClassList.h"
#include "DataWriter.h"
#include "ResolveContext.h"

#include <QDebug>

Struct_ClassTable::Struct_ClassTable(ClassList const &classList,
                                     quint32 baseAddress,
                                     QList<NativeFunction> const &nativeInterface,
                                     QStringList resourceFiles,
                                     const ResourceEditor::Collection &editors,
                                     const MemoryModel &memoryModel)
    : resourceTable(resourceFiles, editors)
{
    foreach (Class const &classData, classList)
        classes.append(Struct_Class(classData));

    sort();

    for (int i = 0; i < classes.size(); i++)
        classes[i].collectExceptions();

    setStaticDataHandles();
    loadNativeInterface(nativeInterface);
    resolveClassReferences();
    computeClassSizes();
    computeFieldOffsets();
    computeMemoryMap(memoryModel, baseAddress);
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

void Struct_ClassTable::moveClass(int index, QString name)
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
    struct FixedOrder
    {
        int position;
        char const *className;
    };

    static FixedOrder const fixedOrder[] = {
        { 0, "java/lang/Object" },
		{ 1, "java/lang/String" },

        // exceptions
		{ 2, "java/lang/Throwable" },
		{ 3, "java/lang/Exception" },
		{ 4, "java/lang/NullPointerException" },
		{ 5, "java/lang/ArithmeticException" },
		{ 6, "java/lang/NegativeArraySizeException" },
		{ 7, "java/lang/IndexOutOfBoundsException" },
		{ 8, "java/lang/ArrayIndexOutOfBoundsException" },
//	    { 9, "java/lang/IllegalFunctionCallException" },
        { 10, "java/lang/Error" },
		{ 10, "java/lang/LinkageError" },
		{ 11, "java/lang/UnsatisfiedLinkError" },
    };

    static size_t const orderCount = sizeof fixedOrder / sizeof fixedOrder[0];

    for (size_t i = 0; i < orderCount; i++)
    {
        FixedOrder const &info = fixedOrder[i];
        moveClass(info.position, info.className);
    }
}


void Struct_ClassTable::setStaticDataHandles()
{
    for (int i = 0; i < classes.size(); i++)
        classes[i].setStaticDataHandle(i + 1);
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


void Struct_ClassTable::computeClassSizes()
{
    for (int i = 0; i < classes.size(); i++)
        classes[i].computeDataSize();
}


void Struct_ClassTable::computeFieldOffsets()
{
    for (int i = 0; i < classes.size(); i++)
        classes[i].computeFieldOffsets();
}


void Struct_ClassTable::writeStruct(DataWriter &data) const
{
    data.put16(classes.size(), "size");
    data.pad16();

    data.putAddress(resourceTable, "resourceTable");

    foreach (Struct_Class const &classData, classes)
        data.putAddress(classData, "classAddress");
}

void Struct_ClassTable::writeData(DataWriter &data) const
{
    foreach (Struct_Class const &classData, classes)
        classData.write(data);

    resourceTable.write(data);
}


quint32 Struct_ClassTable::computeMemoryMap(MemoryModel const &memoryModel, quint32 baseAddress)
{
    baseAddress = setMemoryAddress(memoryModel, baseAddress);

    for (int i = 0; i < classes.size(); i++)
        baseAddress = classes[i].computeMemoryMap(memoryModel, baseAddress);

    baseAddress = resourceTable.computeMemoryMap(memoryModel, baseAddress);

    return baseAddress;
}


void Struct_ClassTable::printMemoryMap(QTextStream &ts) const
{
    ts << "ClassTable @0x" << hex << structStart << " {\n";

    foreach (Struct_Class const &classData, classes)
        classData.printMemoryMap(ts);

    ts << "}\n";
}
