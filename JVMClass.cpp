#include "JVMClass.h"

#include "ConstantPoolInfo_Class.h"
#include "ConstantPoolInfo_Utf8.h"

#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QStringList>


struct JVMClassPrivate
{
    quint16 minorVersion;
    quint16 majorVersion;
    quint16 accessFlags;
    quint16 thisClass;
    quint16 superClass;

    ConstantPool constantPool;
    Interfaces interfaces;
    Fields fields;
    Methods methods;
    Attributes attributes;

    quint16 staticDataSize;
    quint16 instanceDataSize;
};


JVMClass::JVMClass()
    : d_ptr(new JVMClassPrivate)
{
}

JVMClass::~JVMClass()
{
}

JVMClass::JVMClass(JVMClass const &rhs)
    : d_ptr(rhs.d_ptr)
{
}

JVMClass &JVMClass::operator = (JVMClass const &rhs)
{
    d_ptr = rhs.d_ptr;
    return *this;
}


JVMClass::JVMClass(QDataStream &data)
    : d_ptr(new JVMClassPrivate)
{
    Q_D(JVMClass);

    quint32 magic;
    data >> magic;
    if (magic != 0xCAFEBABE)
        qFatal("wrong header");

    data >> d->minorVersion;
    data >> d->majorVersion;

    d->constantPool = ConstantPool(data);

    data >> d->accessFlags;
    data >> d->thisClass;
    data >> d->superClass;

    d->interfaces = Interfaces(data);
    d->fields = Fields(data, d->constantPool);
    d->methods = Methods(data, d->constantPool);
    d->attributes = Attributes(data, d->constantPool);

    d->staticDataSize = 0;
    d->instanceDataSize = 0;

    foreach (Field const &field, d->fields.fields())
        if (field.isStatic())
            d->staticDataSize += field.dataSize();
        else
            d->instanceDataSize += field.dataSize();
}


JVMClass::JVMClass(const ConstantPool &constantPool)
    : d_ptr(new JVMClassPrivate)
{
    Q_D(JVMClass);

    d->minorVersion = 0;
    d->majorVersion = 1;

    d->constantPool = constantPool;

    d->accessFlags = ACC_PUBLIC;
    d->thisClass = 1;
    d->superClass = 3;

    d->staticDataSize = 0;
    d->instanceDataSize = 0;
}


QString JVMClass::name() const
{
    Q_D(const JVMClass);

    QSharedPointer<ConstantPoolInfo_Class> thisClass = d->constantPool.get<ConstantPoolInfo_Class>(d->thisClass);
    QSharedPointer<ConstantPoolInfo_Utf8> thisClassName = d->constantPool.get<ConstantPoolInfo_Utf8>(thisClass->nameIndex());

    return thisClassName->string();
}

QString JVMClass::superName() const
{
    Q_D(const JVMClass);

    if (d->superClass == 0)
        return "-";

    QSharedPointer<ConstantPoolInfo_Class> superClass = d->constantPool.get<ConstantPoolInfo_Class>(d->superClass);
    QSharedPointer<ConstantPoolInfo_Utf8> superClassName = d->constantPool.get<ConstantPoolInfo_Utf8>(superClass->nameIndex());

    return superClassName->string();
}

quint16 JVMClass::minorVersion() const
{
    Q_D(const JVMClass);
    return d->minorVersion;
}

quint16 JVMClass::majorVersion() const
{
    Q_D(const JVMClass);
    return d->majorVersion;
}

bool JVMClass::isPublic() const
{
    Q_D(const JVMClass);
    return d->accessFlags & ACC_PUBLIC;
}

bool JVMClass::isFinal() const
{
    Q_D(const JVMClass);
    return d->accessFlags & ACC_FINAL;
}

bool JVMClass::isSuper() const
{
    Q_D(const JVMClass);
    return d->accessFlags & ACC_SUPER;
}

bool JVMClass::isInterface() const
{
    Q_D(const JVMClass);
    return d->accessFlags & ACC_INTERFACE;
}

bool JVMClass::isAbstract() const
{
    Q_D(const JVMClass);
    return d->accessFlags & ACC_ABSTRACT;
}

QString JVMClass::flagsString() const
{
    QStringList flags;

    if (isPublic())     flags << "public";
    if (isFinal())      flags << "final";
    if (isSuper())      flags << "super";
    if (isInterface())  flags << "interface";
    if (isAbstract())   flags << "abstract";

    return flags.join(", ");
}

quint16 JVMClass::interfaceCount() const
{
    Q_D(const JVMClass);
    return d->interfaces.count();
}

quint16 JVMClass::fieldCount() const
{
    Q_D(const JVMClass);
    return d->fields.count();
}

quint16 JVMClass::methodCount() const
{
    Q_D(const JVMClass);
    return d->methods.count();
}

ConstantPool const &JVMClass::constantPool() const
{
    Q_D(const JVMClass);
    return d->constantPool;
}

Interfaces const &JVMClass::interfaces() const
{
    Q_D(const JVMClass);
    return d->interfaces;
}

Fields const &JVMClass::fields() const
{
    Q_D(const JVMClass);
    return d->fields;
}

Methods const &JVMClass::methods() const
{
    Q_D(const JVMClass);
    return d->methods;
}

Attributes const &JVMClass::attributes() const
{
    Q_D(const JVMClass);
    return d->attributes;
}

Field const &JVMClass::field(int index) const
{
    Q_D(const JVMClass);
    return d->fields.get(index);
}

Method const &JVMClass::method(int index) const
{
    Q_D(const JVMClass);
    return d->methods.get(index);
}

quint16 JVMClass::staticDataSize() const
{
    Q_D(const JVMClass);
    return d->staticDataSize;
}

quint16 JVMClass::instanceDataSize() const
{
    Q_D(const JVMClass);
    return d->instanceDataSize;
}
