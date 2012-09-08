#include "JVMClassList.h"

#include "ConstantPoolInfo_Class.h"
#include "ConstantPoolInfo_Utf8.h"

#include <QDebug>


static JVMClass parseClass(QFileInfo file)
{
    QFile fh(file.filePath());
    if (!fh.open(QFile::ReadOnly))
        qFatal("unable to open class file: %s", file.fileName().toUtf8().constData());
    QDataStream data(&fh);
    return JVMClass(data);
}

JVMClassList::JVMClassList(QList<QFileInfo> const &files)
{
    reserve(files.size());
    std::transform(files.begin(), files.end(), std::back_inserter(*this), parseClass);

    createArrayClasses();

    for (int i = 0; i < size(); i++)
    {
        JVMClass &classData = (*this)[i];
        QString superName = classData.superName();

        // java.lang.Object
        if (superName.isEmpty())
            continue;

        JVMClass const *superClass = byName(superName);
        if (superClass == NULL)
        {
            qWarning() << "superclass" << superName << "for class" << classData.name() << "not found";
            continue;
        }

        classData.setSuperClass(*superClass);
    }
}


bool JVMClassList::containsName(QString className) const
{
    return byName(className) != NULL;
}

JVMClass const *JVMClassList::byName(QString className) const
{
    foreach (JVMClass const &classData, *this)
        if (classData.name() == className)
            return &classData;
    return NULL;
}

static JVMClass createArrayClass(QString className)
{
    ConstantPoolInfo_Utf8 *thisClassName = new ConstantPoolInfo_Utf8(className);
    ConstantPoolInfo_Utf8 *superClassName = new ConstantPoolInfo_Utf8("java/lang/Object");

    ConstantPoolInfo_Class *thisClassInfo = new ConstantPoolInfo_Class(2);
    ConstantPoolInfo_Class *superClassInfo = new ConstantPoolInfo_Class(4);

    ConstantPool constantPool;

    constantPool.add(thisClassInfo);
    constantPool.add(thisClassName);
    constantPool.add(superClassInfo);
    constantPool.add(superClassName);

    return JVMClass(constantPool);
}

void JVMClassList::createArrayClasses()
{
    foreach (JVMClass const &classData, *this)
    {
        foreach (QSharedPointer<ConstantPoolInfo_Class> referencedClass, classData.constantPool().findAll<ConstantPoolInfo_Class>())
        {
            QSharedPointer<ConstantPoolInfo_Utf8> nameConst = classData.constantPool().get<ConstantPoolInfo_Utf8>(referencedClass->nameIndex());
            QString name = nameConst->string();

            if (name[0] == '[' && !containsName(name))
            {
//                qDebug() << "creating array classes" << name << "and" << "[" + name;
                append(createArrayClass(name));
                if (!containsName("[" + name))
                    append(createArrayClass("[" + name));
            }
        }
    }
}
