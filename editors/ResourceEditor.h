#ifndef RESOURCEEDITOR_H
#define RESOURCEEDITOR_H

#include <QDialog>
#include <QMap>
#include <QList>

#include <typeinfo>

#include "Delegate.h"

class Resource;

class ResourceEditor : protected QDialog
{
    Q_OBJECT

public:
    class Collection
    {
    private:
        ResourceEditor *editor(QString type) const;
        void insert(ResourceEditor *editor);

    public:
        explicit Collection(QWidget *parent);
        ~Collection();

        QString newResource(QString type, QString resourcePath) const;
        void editResource(QString path) const;
        Resource *readResource(QString path) const;

    private:
        // suffix -> editor
        typedef QMap<QString, ResourceEditor *> EditorMap;
        EditorMap editors;
    };

protected:
    explicit ResourceEditor(QWidget *parent);

private:
    QString save(Resource *resource, QString path);
    QString saveAs(Resource *resource, QString resourcePath);

    QString newResource(QString resourcePath);
    void editResource(QString path);

private:
    virtual QString const &fileSuffix() const = 0;
    virtual QString const &fileFilter() const = 0;

    virtual Resource *newResource() = 0;
    virtual Resource *readResource(QDataStream &stream) const = 0;
    virtual void setResource(Resource *resource) = 0;

signals:
    
public slots:

protected:
    typedef Delegate<ResourceEditor *(QWidget *parent)> Constructor;
    static QList<Constructor> &constructors();
};


template<typename EditorT, typename ResourceT>
class ResourceEditorT : public ResourceEditor
{
protected:
    typedef ResourceEditorT Base;

public:
    typedef ResourceT ResourceType;

private:
    ResourceType *readResource(QDataStream &stream) const
    {
        return new ResourceType(stream);
    }

    void setResource(Resource *resource)
    {
        if (resource && !dynamic_cast<ResourceType *>(resource))
            qFatal("Expected type: %s, but got %s", typeid(ResourceType).name(), typeid(*resource).name());
        setResource(static_cast<ResourceType *>(resource));
    }

    virtual void setResource(ResourceType *resource) = 0;

protected:
    explicit ResourceEditorT(QWidget *parent)
        : ResourceEditor(parent)
    {
        // reference static initialiser
        (void)init;
    }

private:
    struct Init
    {
        Init()
        {
            constructors().append(Constructor::constructor<EditorT>());
        }
    };

    static Init init;
};

template<typename EditorT, typename ResourceT>
typename ResourceEditorT<EditorT, ResourceT>::Init ResourceEditorT<EditorT, ResourceT>::init;

#endif // RESOURCEEDITOR_H
