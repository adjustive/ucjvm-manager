#include "Struct_CP_Table.h"

#include "Struct_CP_Dummy.h"
#include "Struct_CP_Class.h"
#include "Struct_CP_Double.h"
#include "Struct_CP_Field.h"
#include "Struct_CP_Float.h"
#include "Struct_CP_Integer.h"
#include "Struct_CP_Long.h"
#include "Struct_CP_Method.h"
#include "Struct_CP_Name.h"
#include "Struct_CP_String.h"
#include "Struct_CP_UTF8.h"

#include "ConstantPool.h"
#include "ConstantPoolVisitor.h"
#include "DataWriter.h"

#include <QTextStream>

class CPMaker : public ConstantPoolVisitor
{
    QList<QSharedPointer<Struct_CP> > &constants;

    void add(QSharedPointer<Struct_CP> cp)
    {
        constants.append(cp);
    }

    void add(Struct_CP *cp)
    {
        add(QSharedPointer<Struct_CP>(cp));
    }

    void visit(const ConstantPoolInfo_Dummy &v)
    {
        Q_UNUSED(v);
        add(Struct_CP_Dummy::instance);
    }

    void visit(const ConstantPoolInfo_Class &v)
	{
        add(new Struct_CP_Class(v));
	}

    void visit(const ConstantPoolInfo_Double &v)
	{
        add(new Struct_CP_Double(v));
	}

    void visit(const ConstantPoolInfo_Fieldref &v)
	{
        add(new Struct_CP_Field(v));
	}

    void visit(const ConstantPoolInfo_Float &v)
	{
        add(new Struct_CP_Float(v));
	}

    void visit(const ConstantPoolInfo_Integer &v)
	{
        add(new Struct_CP_Integer(v));
	}

    void visit(const ConstantPoolInfo_InterfaceMethodref &v)
	{
        qFatal("unimplemented: ConstantPoolInfo_InterfaceMethodref");
	}

    void visit(const ConstantPoolInfo_Long &v)
	{
        add(new Struct_CP_Long(v));
	}

    void visit(const ConstantPoolInfo_Methodref &v)
	{
        add(new Struct_CP_Method(v));
	}

    void visit(const ConstantPoolInfo_NameAndType &v)
	{
        add(new Struct_CP_Name(v));
	}

    void visit(const ConstantPoolInfo_String &v)
	{
        add(new Struct_CP_String(v));
	}

    void visit(const ConstantPoolInfo_Utf8 &v)
	{
        add(new Struct_CP_UTF8(v));
	}


public:
    CPMaker(QList<QSharedPointer<Struct_CP> > &constants)
        : constants(constants)
    {
    }
};


Struct_CP_Table::Struct_CP_Table(ConstantPool const &constantPool)
{
    CPMaker v(constants);
    constantPool.accept(v);
}

void Struct_CP_Table::resolveClassReferences(ResolveContext const &context)
{
    foreach (QSharedPointer<Struct_CP> cp, constants)
        cp->resolveClassReferences(context);
}

void Struct_CP_Table::resolveFieldReferences(const ResolveContext &context)
{
    foreach (QSharedPointer<Struct_CP> cp, constants)
        cp->resolveFieldReferences(context);
}

void Struct_CP_Table::resolveMethodReferences(const ResolveContext &context)
{
    foreach (QSharedPointer<Struct_CP> cp, constants)
        cp->resolveMethodReferences(context);
}

void Struct_CP_Table::writeStruct(DataWriter &data) const
{
    data.put16(constants.size(), "size");
    data.pad16();

    foreach (QSharedPointer<Struct_CP> cp, constants)
        data.putAddress(cp, "constant");
}

void Struct_CP_Table::writeData(DataWriter &data) const
{
    foreach (QSharedPointer<Struct_CP> cp, constants)
        cp->write(data);
}

quint32 Struct_CP_Table::computeMemoryMap(const MemoryModel &memoryModel, quint32 baseAddress)
{
    baseAddress = setMemoryAddress(memoryModel, baseAddress);

    foreach (QSharedPointer<Struct_CP> cp, constants)
        baseAddress = cp->computeMemoryMap(memoryModel, baseAddress);

    return baseAddress;
}

void Struct_CP_Table::printMemoryMap(QTextStream &ts) const
{
    ts << "CP_Table @0x" << structStart << " {\n";

    int i = 1;
    foreach (QSharedPointer<Struct_CP> cp, constants)
    {
        ts << "      [" << i << "] = ";
        cp->printMemoryMap(ts);
        i++;
    }
    ts << "    }\n";
}


QString Struct_CP_Table::getUtf8(int index) const
{
    QSharedPointer<Struct_CP_UTF8> utf8Info = constants[index - 1].dynamicCast<Struct_CP_UTF8>();
    if (!utf8Info)
        qFatal("constant %d is %s, not UTF8", index, typeid(*constants[index - 1]).name());
    return utf8Info->string();
}

Struct_CP_Class &Struct_CP_Table::getClass(int index) const
{
    QSharedPointer<Struct_CP_Class> classInfo = constants[index - 1].dynamicCast<Struct_CP_Class>();
    if (!classInfo)
        qFatal("constant %d is %s, not Class", index, typeid(*constants[index - 1]).name());
    return *classInfo;
}

Struct_CP_Name const &Struct_CP_Table::getName(int index) const
{
    QSharedPointer<Struct_CP_Name> classInfo = constants[index - 1].dynamicCast<Struct_CP_Name>();
    if (!classInfo)
        qFatal("constant %d is %s, not Name", index, typeid(*constants[index - 1]).name());
    return *classInfo;
}
