#ifndef METHODS_H
#define METHODS_H

#include <QList>

#include "Method.h"

class Methods
{
public:
    Methods();
    Methods(QDataStream &data, ConstantPool const &cp);

    quint16 count() const;
    Method const &get(int index) const;

private:
    QList<Method> methods;
};

#endif // METHODS_H
