#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <QList>

#include "AttributesInfo.h"

class Attributes
{
public:
    Attributes();
    Attributes(QDataStream &data, ConstantPool const &cp);

    template<typename T>
    QSharedPointer<T> find() const
    {
        foreach (QSharedPointer<AttributesInfo> info, attributes)
        {
            QSharedPointer<T> attribute = info.dynamicCast<T>();
            if (attribute)
                return attribute;
        }

        return QSharedPointer<T>();
    }

private:
    QList<QSharedPointer<AttributesInfo> > attributes;
};

#endif // ATTRIBUTES_H
