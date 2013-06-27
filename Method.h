#ifndef METHOD_H
#define METHOD_H

#include <QDataStream>

#include "Attributes.h"
#include "ConstantPool.h"
#include "ConstantPoolInfo_Utf8.h"
#include "ExceptionHandler.h"

struct MethodPrivate
{
    quint16 accessFlags;
    quint16 nameIndex;
    quint16 descriptorIndex;

    QByteArray parameters;

    QSharedPointer<ConstantPoolInfo_Utf8> methodName;
    QSharedPointer<ConstantPoolInfo_Utf8> methodDescriptor;

    Attributes attributes;
};

class Method
{
public:
	enum Access
	{
		ACC_PUBLIC   		= 0x0001, //  Declared public; may be accessed from outside its package.
		ACC_PRIVATE  		= 0x0002, //  Declared private; accessible only within the defining class.
		ACC_PROTECTED  		= 0x0004, //  Declared protected; may be accessed within subclasses.
		ACC_STATIC  		= 0x0008, //  Declared static.
		ACC_FINAL  			= 0x0010, //  Declared final; may not be overridden.
		ACC_SYNCHRONIZED	= 0x0020, //  Declared synchronized; invocation is wrapped in a monitor lock.
		ACC_NATIVE  		= 0x0100, //  Declared native; implemented in a language other than Java.
		ACC_ABSTRACT  		= 0x0400, //  Declared abstract; no implementation is provided.
        ACC_STRICTFP  		= 0x0800  //  Declared strictfp; floating-point mode is FP-strict
	};

public:
    explicit Method(QDataStream &data, ConstantPool const &cp);

    quint16 accessFlags() const;
    quint16 nameIndex() const;
    quint16 descriptorIndex() const;

    QString name() const;
    QString descriptor() const;

    QByteArray parameters() const;

    quint16 maxStack() const;
    quint16 maxLocals() const;
    QByteArray code() const;

    QList<quint16> exceptions() const;
    QList<ExceptionHandler> exceptionHandlers() const;

    bool isPublic() const;
    bool isPrivate() const;
    bool isProtected() const;
    bool isStatic() const;
    bool isFinal() const;
    bool isSynchronized() const;
    bool isNative() const;
    bool isAbstract() const;
    bool isStrictfp() const;

    QString flagsString() const;

private:
    MethodPrivate d;
};

#endif // METHOD_H
