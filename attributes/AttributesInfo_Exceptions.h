#ifndef ATTRIBUTESINFO_EXCEPTIONS_H
#define ATTRIBUTESINFO_EXCEPTIONS_H

#include "AttributesInfo.h"

#include <QList>

struct AttributesInfo_ExceptionsPrivate
{
    QList<quint16> exceptionTable;
};

class AttributesInfo_Exceptions : public AttributesInfo
{
public:
    AttributesInfo_Exceptions(QDataStream &data);

    QList<quint16> exceptions() const;

private:
    AttributesInfo_ExceptionsPrivate d;
};

#endif // ATTRIBUTESINFO_EXCEPTIONS_H
