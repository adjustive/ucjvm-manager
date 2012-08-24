#ifndef INTERFACES_H
#define INTERFACES_H

#include <QList>

#include "AttributesInfo.h"

class Interfaces
{
public:
    struct Info
    {
        QList<AttributesInfo> attributes;
        quint16 nameIndex;

        Info();
        explicit Info(QDataStream &data);
    };

    Interfaces();
    Interfaces(QDataStream &data);

    quint16 count() const;

private:
    QList<Info> interfaces;
};

#endif // INTERFACES_H
