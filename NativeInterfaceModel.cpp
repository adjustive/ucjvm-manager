#include "NativeInterfaceModel.h"

NativeInterfaceModel::NativeInterfaceModel(QList<NativeFunction> functions, QObject *parent)
    : QAbstractTableModel(parent)
    , functions(functions)
{
}

int NativeInterfaceModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return functions.size();
}

int NativeInterfaceModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5;
}

QVariant NativeInterfaceModel::data(const QModelIndex &index, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        NativeFunction const &function = functions[index.row()];
        switch (index.column())
        {
        case 0: return function.id;
        case 1: return function.className;
        case 2: return function.name;
        case 3: return function.params;
        case 4: return function.description;
        }

        break;
    }

    return QVariant();
}

QVariant NativeInterfaceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        switch (orientation)
        {
        case Qt::Horizontal:
            switch (section)
            {
            case 0: return tr("Id");
            case 1: return tr("Class name");
            case 2: return tr("Function name");
            case 3: return tr("Parameters");
            case 4: return tr("Description");
            }
            break;
        case Qt::Vertical:
            break;
        }

        break;
    }

    return QVariant();
}
