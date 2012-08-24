#include "AttributesInfo.h"
#include "ConstantPool.h"
#include "ConstantPoolInfo_Utf8.h"

#include "AttributesInfo_ConstantValue.h"
#include "AttributesInfo_Code.h"
#include "AttributesInfo_Exceptions.h"
#include "AttributesInfo_InnerClasses.h"
#include "AttributesInfo_Synthetic.h"
#include "AttributesInfo_SourceFile.h"
#include "AttributesInfo_LineNumberTable.h"
#include "AttributesInfo_LocalVariableTable.h"
#include "AttributesInfo_Deprecated.h"
#include "AttributesInfo_StackMapTable.h"
#include "AttributesInfo_Signature.h"

#include <QDebug>

AttributesInfo::AttributesInfo()
{
}

AttributesInfo::~AttributesInfo()
{
}


QSharedPointer<AttributesInfo> AttributesInfo::parse(QDataStream &data, ConstantPool const &cp)
{
    quint16 attributeIndex;
    data >> attributeIndex;

    quint32 attributeDataLength;
    data >> attributeDataLength;

    QSharedPointer<ConstantPoolInfo_Utf8> attributeName = cp.get<ConstantPoolInfo_Utf8>(attributeIndex);

    AttributesInfo *info;

    if (attributeName->string() == "ConstantValue")
    {
        info = new AttributesInfo_ConstantValue(data);
    }

    else if (attributeName->string() == "Code")
    {
        info = new AttributesInfo_Code(data, cp);
    }

    else if (attributeName->string() == "Exceptions")
    {
        info = new AttributesInfo_Exceptions(data);
    }

    else if (attributeName->string() == "InnerClasses")
    {
        data.skipRawData(attributeDataLength);
        info = new AttributesInfo_InnerClasses(data);
    }

    else if (attributeName->string() == "Synthetic")
    {
        info = new AttributesInfo_Synthetic();
    }

    else if (attributeName->string() == "SourceFile")
    {
        info = new AttributesInfo_SourceFile(data);
    }

    else if (attributeName->string() == "LineNumberTable")
    {
        data.skipRawData(attributeDataLength);
        info = new AttributesInfo_LineNumberTable();
    }

    else if (attributeName->string() == "LocalVariableTable")
    {
        data.skipRawData(attributeDataLength);
        info = new AttributesInfo_LocalVariableTable();
    }

    else if (attributeName->string() == "Deprecated")
    {
        info = new AttributesInfo_Deprecated();
    }

    else if (attributeName->string() == "StackMapTable")
    {
        data.skipRawData(attributeDataLength);
        info = new AttributesInfo_StackMapTable();
    }

    else if (attributeName->string() == "Signature")
    {
        info = new AttributesInfo_Signature(data);
    }

    else
    {
        data.skipRawData(attributeDataLength);
        info = NULL;
        qWarning("unknown attribute name: %s", attributeName->string().toUtf8().constData());
    }

    return QSharedPointer<AttributesInfo>(info);
}
