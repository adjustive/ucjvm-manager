#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QAbstractTableModel>
#include <QTime>

class MessageModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    static const char *msgTypeString(QtMsgType type);

    explicit MessageModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void append(QtMsgType type, char const *message);

signals:
    void messageAdded();

private:
    struct Message
    {
        QTime time;
        QtMsgType type;
        QString message;

        Message()
        {
        }

        Message(QtMsgType type, QString message)
            : time(QTime::currentTime())
            , type(type)
            , message(message)
        {
        }
    };

    QList<Message> messages;
};

#endif // MESSAGEMODEL_H
