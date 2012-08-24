#ifndef CONSTANTPOOL_H
#define CONSTANTPOOL_H

#include <QList>
#include <QSharedPointer>

#include "ConstantPoolInfo.h"

#include <typeinfo>

class ConstantPool
{
public:
    ConstantPool();

    void parse(QDataStream &data);

    void add(ConstantPoolInfo *constant);

    template<typename T>
    QSharedPointer<T> get(int index) const
    {
        QSharedPointer<ConstantPoolInfo> constant = constants[index - 1];
        return constant.dynamicCast<T>();
    }

    template<typename T>
    QList<QSharedPointer<T> > findAll() const
    {
        QList<QSharedPointer<T> > found;
        foreach (QSharedPointer<ConstantPoolInfo> constant, constants)
            if (QSharedPointer<T> candidate = constant.dynamicCast<T>())
                found.append(candidate);

        return found;
    }

private:
    QList<QSharedPointer<ConstantPoolInfo> > constants;
};

#endif // CONSTANTPOOL_H
