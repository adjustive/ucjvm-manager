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
    ConstantPool(QDataStream &data);

    void add(ConstantPoolInfo *constant);
    void accept(ConstantPoolVisitor &v) const;

    template<typename T>
    QSharedPointer<T> get(int index) const
    {
        QSharedPointer<ConstantPoolInfo> constant = constantList[index - 1];
        return constant.dynamicCast<T>();
    }

    template<typename T>
    QList<QSharedPointer<T> > findAll() const
    {
        QList<QSharedPointer<T> > found;
        foreach (QSharedPointer<ConstantPoolInfo> constant, constantList)
            if (QSharedPointer<T> candidate = constant.dynamicCast<T>())
                found.append(candidate);

        return found;
    }

private:
    QList<QSharedPointer<ConstantPoolInfo> > constantList;
};

#endif // CONSTANTPOOL_H
