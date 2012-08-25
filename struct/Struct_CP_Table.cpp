#include "Struct_CP_Table.h"

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

#include <QTextStream>

class CPMaker : public ConstantPoolVisitor
{
    QList<QSharedPointer<Struct_CP> > &constants;

    void add(Struct_CP *cp)
    {
        constants.append(QSharedPointer<Struct_CP>(cp));
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

void Struct_CP_Table::writeStruct(DataWriter &data) const
{
}

quint32 Struct_CP_Table::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);

    foreach (QSharedPointer<Struct_CP> cp, constants)
        baseAddress = cp->computeMemoryMap(baseAddress);

    return baseAddress;
}

void Struct_CP_Table::printMemoryMap(QTextStream &ts) const
{
    ts << "CP_Table @0x" << memoryAddress << " {\n";

    int i = 1;
    foreach (QSharedPointer<Struct_CP> cp, constants)
    {
        ts << "      [" << i << "] = ";
        cp->printMemoryMap(ts);
        i++;
    }
    ts << "    }\n";
}
