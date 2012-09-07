#include "Field.h"

#include "ConstantPool.h"
#include "AttributesInfo_ConstantValue.h"

#include <QStringList>

Field::Field()
{
}

Field::Field(QDataStream &data, ConstantPool const &cp)
{
    data >> d.accessFlags;
    data >> d.nameIndex;
    data >> d.descriptorIndex;

    d.fieldName = cp.get<ConstantPoolInfo_Utf8>(d.nameIndex);
    d.fieldDescriptor = cp.get<ConstantPoolInfo_Utf8>(d.descriptorIndex);
    d.attributes = Attributes(data, cp);
}


quint16 Field::accessFlags() const { return d.accessFlags; }
quint16 Field::nameIndex() const { return d.nameIndex; }
quint16 Field::descriptorIndex() const { return d.descriptorIndex; }

Field::FieldType Field::dataType() const
{
    switch (d.fieldDescriptor->string()[0].toAscii())
    {
    case 'B': return FIELD_TYPE_BYTE;
    case 'C': return FIELD_TYPE_CHAR;
    case 'F': return FIELD_TYPE_FLOAT;
    case 'I': return FIELD_TYPE_INT;
    case 'S': return FIELD_TYPE_SHORT;
    case 'Z': return FIELD_TYPE_BOOLEAN;
    case 'L': return FIELD_TYPE_CLASS_REFERENCE;
    case '[': return FIELD_TYPE_ARRAY_REFERENCE;
    case 'D': return FIELD_TYPE_DOUBLE;
    case 'J': return FIELD_TYPE_LONG;
    }

    qFatal("unknown field type");
}

QString Field::name() const { return d.fieldName->string(); }
QString Field::descriptor() const { return d.fieldDescriptor->string(); }

bool Field::isPublic() const { return d.accessFlags & ACC_PUBLIC; }
bool Field::isPrivate() const { return d.accessFlags & ACC_PRIVATE; }
bool Field::isProtected() const { return d.accessFlags & ACC_PROTECTED; }
bool Field::isStatic() const { return d.accessFlags & ACC_STATIC; }
bool Field::isFinal() const { return d.accessFlags & ACC_FINAL; }
bool Field::isVolatile() const { return d.accessFlags & ACC_VOLATILE; }
bool Field::isTransient() const { return d.accessFlags & ACC_TRANSIENT; }

QString Field::flagsString() const
{
    QStringList flags;

    if (isPublic())     flags << "public";
    if (isPrivate())    flags << "private";
    if (isProtected())  flags << "protected";
    if (isStatic())     flags << "static";
    if (isFinal())      flags << "final";
    if (isVolatile())   flags << "volatile";
    if (isTransient())  flags << "transient";

    return flags.join(" ");
}

quint16 Field::dataSize() const
{
    switch (dataType())
    {
	case FIELD_TYPE_BYTE:
    case FIELD_TYPE_BOOLEAN:
        return 1;

    case FIELD_TYPE_CHAR:
    case FIELD_TYPE_SHORT:
        return 2;

    case FIELD_TYPE_INT:
	case FIELD_TYPE_FLOAT:
    case FIELD_TYPE_ARRAY_REFERENCE:
    case FIELD_TYPE_CLASS_REFERENCE:
        return 4;

    case FIELD_TYPE_LONG:
	case FIELD_TYPE_DOUBLE:
        return 8;
    }

    throw;
}

quint16 Field::constantValueIndex() const
{
    QSharedPointer<AttributesInfo_ConstantValue> value = d.attributes.find<AttributesInfo_ConstantValue>();
    if (!value)
        return 0;
    return value->constantValueIndex();
}
