#ifndef ATTRIBUTESINFO_CODE_H
#define ATTRIBUTESINFO_CODE_H

#include "Attributes.h"
#include "ExceptionHandlers.h"

class AttributesInfo_CodePrivate
{
public:
    Attributes attributes;

    quint16 maxStack;
    quint16 maxLocals;

    QByteArray code;

    ExceptionHandlers exceptionHandlers;
};

class AttributesInfo_Code : public AttributesInfo
{
public:
    AttributesInfo_Code(QDataStream &data, ConstantPool const &cp);

    quint16 maxStack() const;
    quint16 maxLocals() const;

    QByteArray code() const;

    QList<ExceptionHandler> exceptionHandlers() const;

private:
    AttributesInfo_CodePrivate d;
};

#endif // ATTRIBUTESINFO_CODE_H
