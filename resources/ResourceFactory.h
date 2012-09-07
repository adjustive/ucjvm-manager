#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H

#include "Resource.h"

#include <QSharedPointer>
#include <QMap>

class ResourceFactory
{
    struct Constructor
    {
        virtual ~Constructor() { }
        virtual Resource *create(QDataStream &stream) const = 0;
    };

    template<typename T>
    struct TypeConstructor : Constructor
    {
        typedef typename T::ResourceType ResourceType;

        ResourceType *create(QDataStream &stream) const
        {
            return new ResourceType(stream);
        }
    };

    typedef QMap<QString, QSharedPointer<Constructor> > ConstructorMap;
    ConstructorMap constructors;

public:
    ResourceFactory();

    template<typename T>
    void addConstructor(QString suffix)
    {
        Q_ASSERT(!constructors.contains(suffix));
        constructors.insert(suffix, QSharedPointer<Constructor>(new TypeConstructor<T>()));
    }

    Resource *create(QString suffix, QDataStream &stream) const;

    static ResourceFactory &instance();

    template<typename T>
    struct Insert
    {
        Insert()
        {
            instance().addConstructor<T>(T::fileSuffix);
        }
    };
};

#endif // RESOURCEFACTORY_H
