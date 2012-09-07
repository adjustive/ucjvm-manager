#include "ResourceFactory.h"

#include <QDebug>


ResourceFactory &ResourceFactory::instance()
{
    static ResourceFactory instance;
    return instance;
}


ResourceFactory::ResourceFactory()
{
}


Resource *ResourceFactory::create(QString suffix, QDataStream &stream) const
{
    ConstructorMap::const_iterator found = constructors.find(suffix);
    if (found == constructors.end())
    {
        qWarning() << "could not find resource constructor for suffix" << suffix;
        return NULL;
    }

    return found.value()->create(stream);
}
