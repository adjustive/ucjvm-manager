#ifndef METHODS_H
#define METHODS_H

#include <QList>

#include "Method.h"

struct MethodsPrivate
{
    QList<Method> methods;
};

class Methods
{
public:
    Methods();
    Methods(QDataStream &data, ConstantPool const &cp);

    quint16 count() const;
    Method const &get(int index) const;
    QList<Method> methods() const;

private:
    MethodsPrivate d;
};

#endif // METHODS_H
