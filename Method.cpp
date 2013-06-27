#include "Method.h"

#include "AttributesInfo_Code.h"
#include "AttributesInfo_Exceptions.h"

#include <QDebug>
#include <QStringList>

Method::Method(QDataStream &data, ConstantPool const &cp)
{
    data >> d.accessFlags;
    data >> d.nameIndex;
    data >> d.descriptorIndex;

    d.methodName = cp.get<ConstantPoolInfo_Utf8>(d.nameIndex);
    d.methodDescriptor = cp.get<ConstantPoolInfo_Utf8>(d.descriptorIndex);

    QString const &descriptor = d.methodDescriptor->string();
    QString::const_iterator it = descriptor.constBegin();

    Q_ASSERT(*it == '(');
    ++it;

    QString callParams;
    while (*it != ')')
    {
        callParams += *it;

        while (*it == '[')
            ++it;

        if (*it == 'L')
            while (*it != ';')
                ++it;

        ++it;
    }
    callParams += *++it;

    d.parameters = callParams.toAscii();
//    qDebug() << "Parsed" << descriptor << "to" << callParams;

    d.attributes = Attributes(data, cp);
}

quint16 Method::accessFlags() const
{
    return d.accessFlags;
}

quint16 Method::nameIndex() const
{
    return d.nameIndex;
}

quint16 Method::descriptorIndex() const
{
    return d.descriptorIndex;
}

QString Method::name() const
{
    return d.methodName->string();
}

QString Method::descriptor() const
{
    return d.methodDescriptor->string();
}

QByteArray Method::parameters() const
{
    return d.parameters;
}

quint16 Method::maxStack() const
{
    QSharedPointer<AttributesInfo_Code> code = d.attributes.find<AttributesInfo_Code>();
    if (!code)
        return 0;
    return code->maxStack();
}

quint16 Method::maxLocals() const
{
    QSharedPointer<AttributesInfo_Code> code = d.attributes.find<AttributesInfo_Code>();
    if (!code)
        return 0;
    return code->maxLocals();
}

QByteArray Method::code() const
{
    QSharedPointer<AttributesInfo_Code> code = d.attributes.find<AttributesInfo_Code>();
    if (!code)
        return QByteArray();
    return code->code();
}

QList<quint16> Method::exceptions() const
{
    QSharedPointer<AttributesInfo_Exceptions> exceptions = d.attributes.find<AttributesInfo_Exceptions>();
    if (!exceptions)
        return QList<quint16>();
    return exceptions->exceptions();
}

QList<ExceptionHandler> Method::exceptionHandlers() const
{
    QSharedPointer<AttributesInfo_Code> code = d.attributes.find<AttributesInfo_Code>();
    if (!code)
        return QList<ExceptionHandler>();
    return code->exceptionHandlers();
}

bool Method::isPublic() const { return d.accessFlags & ACC_PUBLIC; }
bool Method::isPrivate() const { return d.accessFlags & ACC_PRIVATE; }
bool Method::isProtected() const { return d.accessFlags & ACC_PROTECTED; }
bool Method::isStatic() const { return d.accessFlags & ACC_STATIC; }
bool Method::isFinal() const { return d.accessFlags & ACC_FINAL; }
bool Method::isSynchronized() const { return d.accessFlags & ACC_SYNCHRONIZED; }
bool Method::isNative() const { return d.accessFlags & ACC_NATIVE; }
bool Method::isAbstract() const { return d.accessFlags & ACC_ABSTRACT; }
bool Method::isStrictfp() const { return d.accessFlags & ACC_STRICTFP; }

QString Method::flagsString() const
{
    QStringList flags;

    if (isPublic())       flags << "public";
    if (isPrivate())      flags << "private";
    if (isProtected())    flags << "protected";
    if (isStatic())       flags << "static";
    if (isFinal())        flags << "final";
    if (isSynchronized()) flags << "synchronized";
    if (isNative())       flags << "native";
    if (isAbstract())     flags << "abstract";
    if (isStrictfp())     flags << "strictfp";

    return flags.join(" ");
}
