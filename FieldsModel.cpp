#include "FieldsModel.h"

#include <JavaName.h>

FieldsModel::FieldsModel(JVMClass classData, QObject *parent)
    : QAbstractTableModel(parent)
    , classData(classData)
{
}

int FieldsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return classData.fieldCount();
}

int FieldsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

QVariant FieldsModel::data(const QModelIndex &index, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        Field const &field = classData.field(index.row());
        switch (index.column())
        {
        case 0:
            return field.flagsString();
        case 1:
            return JavaName::demangle(field.descriptor());
        case 2:
            return field.name();
        }

        break;
    }

    return QVariant();
}

QVariant FieldsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        switch (orientation)
        {
        case Qt::Horizontal:
            switch (section)
            {
            case 0: return "Flags";
            case 1: return "Type";
            case 2: return "Field name";
            }
            break;
        case Qt::Vertical:
            break;
        }

        break;
    }

    return QVariant();
}
