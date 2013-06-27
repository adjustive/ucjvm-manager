#include "MessageModel.h"

char const *MessageModel::msgTypeString(QtMsgType type)
{
    switch (type)
    {
    case QtDebugMsg: return "Debug";
    case QtWarningMsg: return "Warning";
    case QtCriticalMsg: return "Critical";
    case QtFatalMsg: return "Fatal";
    }

    return "<invalid>";
}


MessageModel::MessageModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int MessageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return messages.size();
}

int MessageModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

QVariant MessageModel::data(const QModelIndex &index, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        switch (index.column())
        {
        case 0:
            return messages[index.row()].time.toString(Qt::ISODate);
        case 1:
            return msgTypeString(messages[index.row()].type);
        case 2:
            return messages[index.row()].message;
        }

        break;
    }

    return QVariant();
}

QVariant MessageModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        switch (orientation)
        {
        case Qt::Horizontal:
            switch (section)
            {
            case 0: return tr("Time");
            case 1: return tr("Type");
            case 2: return tr("Message");
            }
            break;
        case Qt::Vertical:
            break;
        }

        break;
    }

    return QVariant();
}


void MessageModel::append(QtMsgType type, const char *message)
{
    int count = rowCount(QModelIndex());

    beginInsertRows(QModelIndex(), count, count);
    messages.append(Message(type, message));
    endInsertRows();

    emit messageAdded();
}
