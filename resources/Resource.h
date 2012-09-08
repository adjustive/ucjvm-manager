#ifndef RESOURCE_H
#define RESOURCE_H

class QDataStream;

class ResourceVisitor;

class Resource
{
public:
    Resource();
    virtual ~Resource();

    virtual void accept(ResourceVisitor &v) = 0;
    virtual void save(QDataStream &stream) const = 0;
};

#endif // RESOURCE_H
