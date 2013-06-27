#ifndef ATTRIBUTEINFO_H
#define ATTRIBUTEINFO_H

#include <QByteArray>
#include <QSharedPointer>

class ConstantPool;

class AttributesInfo
{
public:
    AttributesInfo();
    virtual ~AttributesInfo();

    static QSharedPointer<AttributesInfo> parse(QDataStream &data, ConstantPool const &cp);
};

#endif // ATTRIBUTEINFO_H
