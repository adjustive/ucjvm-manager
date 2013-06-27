#ifndef FIELD_H
#define FIELD_H

#include <QList>
#include <QSharedPointer>

#include "ConstantPoolInfo_Utf8.h"
#include "Attributes.h"

struct FieldPrivate
{
    quint16 accessFlags;
    quint16 nameIndex;
    quint16 descriptorIndex;

    QSharedPointer<ConstantPoolInfo_Utf8> fieldName;
    QSharedPointer<ConstantPoolInfo_Utf8> fieldDescriptor;

    Attributes attributes;
};


class Field
{
public:
	enum Access
	{
		ACC_PUBLIC		= 0x0001,
		ACC_PRIVATE		= 0x0002,
		ACC_PROTECTED	= 0x0004,
		ACC_STATIC		= 0x0008,
		ACC_FINAL		= 0x0010,
		ACC_VOLATILE	= 0x0040,
		ACC_TRANSIENT	= 0x0080
	};

	enum FieldType
	{
        FIELD_TYPE_BYTE				= 1,
		FIELD_TYPE_CHAR				= 2,
		FIELD_TYPE_INT				= 3,
		FIELD_TYPE_FLOAT			= 4,
		FIELD_TYPE_SHORT			= 5,
                                       
		FIELD_TYPE_LONG				= 6,
		FIELD_TYPE_DOUBLE			= 7,
		FIELD_TYPE_ARRAY_REFERENCE	= 8,
		FIELD_TYPE_CLASS_REFERENCE	= 9,
        FIELD_TYPE_BOOLEAN			= 10
	};

public:
    Field();
    Field(QDataStream &data, ConstantPool const &cp);

    quint16 accessFlags() const;
    quint16 nameIndex() const;
    quint16 descriptorIndex() const;
    FieldType dataType() const;

    QString name() const;
    QString descriptor() const;

    bool isPublic() const;
    bool isPrivate() const;
    bool isProtected() const;
    bool isStatic() const;
    bool isFinal() const;
    bool isVolatile() const;
    bool isTransient() const;

    QString flagsString() const;

    quint16 dataSize() const;
    quint16 constantValueIndex() const;

private:
    FieldPrivate d;
};

#endif // FIELD_H
