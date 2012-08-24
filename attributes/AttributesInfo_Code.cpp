#include "AttributesInfo_Code.h"

#include <QDataStream>

AttributesInfo_Code::AttributesInfo_Code(QDataStream &data, ConstantPool const &cp)
{
    data >> d.maxStack;
    data >> d.maxLocals;

    quint32 codeLength;
    char *codeBytes;
    data.readBytes(codeBytes, codeLength);
    d.code = QByteArray(codeBytes, codeLength);
    delete[] codeBytes;

    d.exceptionHandlers = ExceptionHandlers(data);

    d.attributes = Attributes(data, cp);
}


quint16 AttributesInfo_Code::maxStack() const
{
    return d.maxStack;
}

quint16 AttributesInfo_Code::maxLocals() const
{
    return d.maxLocals;
}

QByteArray AttributesInfo_Code::code() const
{
    return d.code;
}

QList<ExceptionHandler> AttributesInfo_Code::exceptionHandlers() const
{
    return d.exceptionHandlers.handlers();
}
