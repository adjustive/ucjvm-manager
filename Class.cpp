#include "Class.h"

#include "ConstantPoolInfo_Class.h"
#include "ConstantPoolInfo_Utf8.h"

#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QStringList>


struct ClassPrivate
{
    quint16 minorVersion;
    quint16 majorVersion;
    quint16 accessFlags;
    quint16 thisClass;
    quint16 superClass;
    Class const *superClassPointer;

    ConstantPool constantPool;
    Interfaces interfaces;
    Fields fields;
    Methods methods;
    Attributes attributes;

    quint16 staticDataSize;
    quint16 instanceDataSize;
};


Class::Class()
    : d_ptr(NULL)
{
}

Class::~Class()
{
}

Class::Class(Class const &rhs)
    : d_ptr(rhs.d_ptr)
{
}

Class &Class::operator = (Class const &rhs)
{
    d_ptr = rhs.d_ptr;
    return *this;
}


Class::Class(QDataStream &data)
    : d_ptr(new ClassPrivate)
{
    Q_D(Class);

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
    d->superClassPointer = NULL;

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


Class::Class(const ConstantPool &constantPool)
    : d_ptr(new ClassPrivate)
{
    Q_D(Class);

    d->minorVersion = 0;
    d->majorVersion = 1;

    d->constantPool = constantPool;

    d->accessFlags = ACC_PUBLIC;
    d->thisClass = 1;
    d->superClass = 3;
    d->superClassPointer = NULL;

    d->staticDataSize = 0;
    d->instanceDataSize = 0;
}


void Class::setSuperClass(Class const &classData)
{
    Q_D(Class);
    d->superClassPointer = &classData;
}


QString Class::name() const
{
    Q_D(const Class);

    QSharedPointer<ConstantPoolInfo_Class> thisClass = d->constantPool.get<ConstantPoolInfo_Class>(d->thisClass);
    QSharedPointer<ConstantPoolInfo_Utf8> thisClassName = d->constantPool.get<ConstantPoolInfo_Utf8>(thisClass->nameIndex());

    return thisClassName->string();
}

QString Class::superName() const
{
    Q_D(const Class);

    if (d->superClass == 0)
        return QString();

    QSharedPointer<ConstantPoolInfo_Class> superClass = d->constantPool.get<ConstantPoolInfo_Class>(d->superClass);
    QSharedPointer<ConstantPoolInfo_Utf8> superClassName = d->constantPool.get<ConstantPoolInfo_Utf8>(superClass->nameIndex());

    return superClassName->string();
}

quint16 Class::minorVersion() const
{
    Q_D(const Class);
    return d->minorVersion;
}

quint16 Class::majorVersion() const
{
    Q_D(const Class);
    return d->majorVersion;
}

bool Class::isPublic() const
{
    Q_D(const Class);
    return d->accessFlags & ACC_PUBLIC;
}

bool Class::isFinal() const
{
    Q_D(const Class);
    return d->accessFlags & ACC_FINAL;
}

bool Class::isSuper() const
{
    Q_D(const Class);
    return d->accessFlags & ACC_SUPER;
}

bool Class::isInterface() const
{
    Q_D(const Class);
    return d->accessFlags & ACC_INTERFACE;
}

bool Class::isAbstract() const
{
    Q_D(const Class);
    return d->accessFlags & ACC_ABSTRACT;
}

QString Class::flagsString() const
{
    QStringList flags;

    if (isPublic())     flags << "public";
    if (isFinal())      flags << "final";
    if (isSuper())      flags << "super";
    if (isInterface())  flags << "interface";
    if (isAbstract())   flags << "abstract";

    return flags.join(", ");
}

quint16 Class::interfaceCount() const
{
    Q_D(const Class);
    return d->interfaces.count();
}

quint16 Class::fieldCount() const
{
    Q_D(const Class);
    return d->fields.count();
}

quint16 Class::methodCount() const
{
    Q_D(const Class);
    return d->methods.count();
}

ConstantPool const &Class::constantPool() const
{
    Q_D(const Class);
    return d->constantPool;
}

Interfaces const &Class::interfaces() const
{
    Q_D(const Class);
    return d->interfaces;
}

Fields const &Class::fields() const
{
    Q_D(const Class);
    return d->fields;
}

Methods const &Class::methods() const
{
    Q_D(const Class);
    return d->methods;
}

Attributes const &Class::attributes() const
{
    Q_D(const Class);
    return d->attributes;
}

Field const &Class::field(int index) const
{
    Q_D(const Class);
    return d->fields.get(index);
}

Method const &Class::method(int index) const
{
    Q_D(const Class);
    return d->methods.get(index);
}

quint16 Class::staticDataSize() const
{
    Q_D(const Class);
    return d->staticDataSize;
}

quint16 Class::instanceDataSize() const
{
    Q_D(const Class);
    return d->instanceDataSize;
}

quint16 Class::inheritedStaticDataSize() const
{
    Q_D(const Class);
    if (d->superClassPointer == NULL)
        return 0;
    return d->superClassPointer->staticDataSize() + d->superClassPointer->inheritedStaticDataSize();
}

quint16 Class::inheritedInstanceDataSize() const
{
    Q_D(const Class);
    if (d->superClassPointer == NULL)
        return 0;
    return d->superClassPointer->instanceDataSize() + d->superClassPointer->inheritedInstanceDataSize();
}
