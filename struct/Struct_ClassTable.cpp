#include "Struct_ClassTable.h"

#include "ClassList.h"
#include "DataWriter.h"
#include "ResolveContext.h"

#include <QDebug>

Struct_ClassTable::Struct_ClassTable(ClassList const &classList, quint32 baseAddress, QList<NativeFunction> const &nativeInterface, QStringList resourceFiles, const ResourceEditor::Collection &editors)
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
    static struct FixedOrder
    {
        int position;
        char const *className;
    } const fixedOrder[] = {
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

    FixedOrder cFixed[] = {
		{ 0, "java/lang/Object" },
		{ 1, "java/lang/String" },
		{ 2, "java/lang/Throwable" },
		{ 3, "java/lang/Exception" },
		{ 4, "java/lang/NullPointerException" },
		{ 5, "java/lang/ArithmeticException" },
		{ 6, "java/lang/NegativeArraySizeException" },
		{ 7, "java/lang/IndexOutOfBoundsException" },
		{ 8, "java/lang/ArrayIndexOutOfBoundsException" },
		{ 9, "testsuite/TestRunner$Derived23" },
		{ 10,"testsuite/TestRunner$Derived15" },
		{ 11,"testsuite/TestRunner$Derived10" },
		{ 12,"testsuite/TestRunner$Derived24" },
		{ 13,"testsuite/TestRunner$Derived16" },
		{ 14,"testsuite/TestRunner$Derived9" },
		{ 15,"testsuite/TestRunner$Derived" },
		{ 16,"testsuite/TestRunner$Derived14" },
		{ 17,"testsuite/TestRunner$1$Foo" },
		{ 18,"testsuite/TestRunner$Derived19" },
		{ 19,"testsuite/TestRunner$Base" },
		{ 20,"testsuite/TestRunner$Derived25" },
		{ 21,"testsuite/TestRunner$Derived26" },
		{ 22,"testsuite/TestRunner$Derived20" },
		{ 23,"testsuite/TestRunner$Derived6" },
		{ 24,"testsuite/TestRunner$1Foo" },
		{ 25,"testsuite/TestRunner$Derived13" },
		{ 26,"testsuite/TestRunner$Derived18" },
		{ 27,"testsuite/TestRunner$Derived2" },
		{ 28,"testsuite/TestRunner$Derived27" },
		{ 29,"testsuite/TestRunner$Derived17" },
		{ 30,"testsuite/TestRunner" },
		{ 31,"testsuite/TestRunner$Derived12" },
		{ 32,"testsuite/TestRunner$Derived4" },
		{ 33,"testsuite/TestRunner$Derived5" },
		{ 34,"testsuite/TestRunner$Derived21" },
		{ 35,"testsuite/TestRunner$Derived11" },
		{ 36,"testsuite/TestRunner$Derived8" },
		{ 37,"testsuite/TestRunner$Derived1" },
		{ 38,"testsuite/TestRunner$Derived3" },
		{ 39,"testsuite/TestRunner$Derived7" },
		{ 40,"testsuite/TestRunner$Derived22" },
		{ 41,"hardware/Display2D" },
		{ 42,"hardware/Logger" },
		{ 43,"hardware/Buzzer" },
		{ 44,"hardware/UI" },
		{ 45,"hardware/LED" },
		{ 46,"utils/RandomNumber" },
		{ 47,"java/io/Console" },
		{ 48,"java/io/File" },
		{ 49,"java/lang/Thread" },
		{ 50,"java/lang/InterruptedException" },
		{ 51,"java/lang/NoSuchFieldError" },
		{ 52,"java/lang/Integer" },
		{ 53,"java/lang/IllegalArgumentException" },
		{ 54,"java/lang/System" },
		{ 55,"java/lang/Enum" },
		{ 56,"java/lang/RuntimeException" },
		{ 57,"java/lang/StringIndexOutOfBoundsException" },
		{ 58,"games/Game" },
		{ 59,"games/Highscore" },
		{ 60,"graphics/Font8x8" },
		{ 61,"graphics/Sprite2D" },
		{ 62,"graphics/Viewport2D" },
		{ 63,"graphics/Coordinate" },
		{ 64,"graphics/Font5x5" },
		{ 65,"graphics/Bitmap2D" },
		{ 66,"graphics/Font" },
		{ 67,"[Ltestsuite/TestRunner;" },
		{ 68,"[[Ltestsuite/TestRunner;" },
		{ 69,"[B" },
		{ 70,"[[B" },
		{ 71,"[C" },
		{ 72,"[[C" },
    };

    FixedOrder const *order = cFixed;
    size_t const orderCount = sizeof cFixed / sizeof cFixed[0];

    for (size_t i = 0; i < orderCount; i++)
    {
        FixedOrder const &info = order[i];
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
        data.put32(classData.structStart, "classAddress");
}

void Struct_ClassTable::writeData(DataWriter &data) const
{
    foreach (Struct_Class const &classData, classes)
        classData.write(data);

    resourceTable.write(data);
}


quint32 Struct_ClassTable::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);

    for (int i = 0; i < classes.size(); i++)
        baseAddress = classes[i].computeMemoryMap(baseAddress);

    baseAddress = resourceTable.computeMemoryMap(baseAddress);

    return baseAddress;
}


void Struct_ClassTable::printMemoryMap(QTextStream &ts) const
{
    ts << "ClassTable @0x" << hex << structStart << " {\n";

    foreach (Struct_Class const &classData, classes)
        classData.printMemoryMap(ts);

    ts << "}\n";
}
