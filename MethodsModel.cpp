#include "MethodsModel.h"

#include "JavaName.h"

MethodsModel::MethodsModel(JVMClass classData, QObject *parent)
    : QAbstractTableModel(parent)
    , classData(classData)
{
}

int MethodsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return classData.methodCount();
}

int MethodsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 6;
}

QVariant MethodsModel::data(const QModelIndex &index, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        Method const &method = classData.method(index.row());
        switch (index.column())
        {
        case 0:
            return method.flagsString();
        case 1:
            return JavaName::demangle(method.descriptor());
        case 2:
            return method.name();
        case 3:
            return method.maxStack();
        case 4:
            return method.maxLocals();
        case 5:
            return method.code().size();
        }

        break;
    }

    return QVariant();
}

QVariant MethodsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        switch (orientation)
        {
        case Qt::Horizontal:
            switch (section)
            {
            case 0: return tr("Flags");
            case 1: return tr("Type");
            case 2: return tr("Method name");
            case 3: return tr("Max stack");
            case 4: return tr("Max locals");
            case 5: return tr("Code size");
            }
            break;
        case Qt::Vertical:
            break;
        }

        break;
    }

    return QVariant();
}
