#include "Struct_ResourceTable.h"

#include "DataWriter.h"
#include "Resource.h"
#include "ResourceVisitor.h"

#include "Struct_Resource_Bitmap2D.h"
#include "Struct_Resource_Bitmap3D.h"

#include <QDebug>
#include <QFileInfo>


class ResourceMaker : public ResourceVisitor
{
    QList<QSharedPointer<Struct_Resource> > &resources;

    void add(QSharedPointer<Struct_Resource> resource)
    {
        resources.append(resource);
    }

    void add(Struct_Resource *resource)
    {
        add(QSharedPointer<Struct_Resource>(resource));
    }


    void visit(Bitmap2D &bitmap)
    {
        add(new Struct_Resource_Bitmap2D(resourceName, bitmap));
    }

    void visit(Bitmap3D &bitmap)
    {
        add(new Struct_Resource_Bitmap3D(resourceName, bitmap));
    }

public:
    ResourceMaker(QList<QSharedPointer<Struct_Resource> > &resources, QString resourceName)
        : resources(resources)
        , resourceName(resourceName)
    {
    }

private:
    QString resourceName;
};


Struct_ResourceTable::Struct_ResourceTable(QStringList resourceFiles, ResourceEditor::Collection const &editors)
{
    foreach (QString const &resourceFile, resourceFiles)
    {
        Resource *resource = editors.readResource(resourceFile);
        Q_ASSERT(resource != NULL);
        ResourceMaker resourceMaker(resources, QFileInfo(resourceFile).fileName());
        resource->accept(resourceMaker);
        delete resource;
    }
}


void Struct_ResourceTable::writeStruct(DataWriter &data) const
{
    data.put32(resources.size(), "size");
    foreach (QSharedPointer<Struct_Resource> const &resource, resources)
        data.putAddress(resource, "resource");
}


void Struct_ResourceTable::writeData(DataWriter &data) const
{
    foreach (QSharedPointer<Struct_Resource> const &resource, resources)
        resource->write(data);
}


quint32 Struct_ResourceTable::computeMemoryMap(const MemoryModel &memoryModel, quint32 baseAddress)
{
    baseAddress = setMemoryAddress(memoryModel, baseAddress);

    foreach (QSharedPointer<Struct_Resource> const &resource, resources)
        baseAddress = resource->computeMemoryMap(memoryModel, baseAddress);

    return baseAddress;
}


void Struct_ResourceTable::printMemoryMap(QTextStream &ts) const
{
}
