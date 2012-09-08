#include "ResourceEditor.h"
#include "Resource.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>


QList<ResourceEditor::Constructor> &ResourceEditor::constructors()
{
    static QList<ResourceEditor::Constructor> constructors;
    return constructors;
}


ResourceEditor *ResourceEditor::Collection::editor(QString type) const
{
    EditorMap::const_iterator found = editors.find(type);
    if (found == editors.end())
    {
        qWarning() << "could not find editor for file type:" << type;
        return NULL;
    }

    return found.value();
}

void ResourceEditor::Collection::insert(ResourceEditor *editor)
{
    Q_ASSERT(!editors.contains(editor->fileSuffix()));
    editors.insert(editor->fileSuffix(), editor);
}


ResourceEditor::Collection::Collection(QWidget *parent)
{
    foreach (Constructor const &ctor, constructors())
        insert(ctor(parent));
}

ResourceEditor::Collection::~Collection()
{
    foreach (ResourceEditor *editor, editors.values())
        delete editor;
}


QString ResourceEditor::Collection::newResource(QString type, QString resourcePath) const
{
    QString fileName;
    if (ResourceEditor *editor = this->editor(type))
        fileName = editor->newResource(resourcePath);
    return fileName;
}

void ResourceEditor::Collection::editResource(QString path) const
{
    QFileInfo info(path);
    if (ResourceEditor *editor = this->editor(info.suffix()))
        editor->editResource(path);
}



ResourceEditor::ResourceEditor(QWidget *parent)
    : QDialog(parent)
{
}


QString ResourceEditor::save(Resource *resource, QString path)
{
    QFile file(path);
    if (!file.open(QFile::WriteOnly))
    {
        QMessageBox::warning(0, tr("Cannot write file"), tr("Unable to open file `%0' for writing").arg(file.fileName()));
        return QString();
    }

    QDataStream stream(&file);
    resource->save(stream);

    return file.fileName();
}


QString ResourceEditor::saveAs(Resource *resource, QString resourcePath)
{
    QFileDialog fileDialog(0, tr("Save resource as"), resourcePath, fileFilter());
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setDefaultSuffix(fileSuffix());

    QString fileName;

    if (fileDialog.exec() == QDialog::Accepted)
        fileName = save(resource, fileDialog.selectedFiles().at(0));

    return fileName;
}


QString ResourceEditor::newResource(QString resourcePath)
{
    QString fileName;

    if (Resource *resource = newResource())
    {
        setResource(resource);
        if (exec() == Accepted)
            fileName = saveAs(resource, resourcePath);
        setResource(NULL);

        delete resource;
    }

    return fileName;
}

void ResourceEditor::editResource(QString path)
{
    QFile resourceFile(path);
    if (!resourceFile.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, tr("Cannot read file"), tr("Unable to open file `%0' for reading").arg(resourceFile.fileName()));
        return;
    }

    QDataStream stream(&resourceFile);
    if (Resource *resource = readResource(stream))
    {
        setResource(resource);
        if (exec() == Accepted)
            save(resource, path);
        setResource(NULL);

        delete resource;
    }
}
