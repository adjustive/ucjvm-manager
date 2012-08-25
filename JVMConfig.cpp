#include "JVMConfig.h"

#include <QXmlSimpleReader>
#include <QDebug>

#include <stdexcept>

struct Handler : QXmlDefaultHandler
{
    bool startElement(const QString &namespaceURI,
                      const QString &localName,
                      const QString &qName,
                      const QXmlAttributes &atts)
    {
        Q_UNUSED(namespaceURI);
        Q_UNUSED(qName);

        if (localName != "entry")
            return true;

        key = atts.value("key");

        return true;
    }

    bool characters(const QString &ch)
    {
        if (key.isEmpty())
            return true;

        if (ch == "\n")
        {
            if (!config.contains(key))
                config.insert(key, "");
            return true;
        }

        config.insert(key, ch);

        return true;
    }

    QString operator[] (QString key) const
    {
        if (!config.contains(key))
        {
            qWarning() << "no such key:" << key;
        }
        return config[key];
    }

private:
    QString key;
    QMap<QString, QString> config;
};

JVMConfig::JVMConfig()
{
}

JVMConfig::JVMConfig(QString path)
{
    QFile file(path);
    if (!file.open(QFile::ReadOnly))
    {
        throw std::runtime_error("could not open file: " + file.fileName().toStdString());
    }

    QXmlInputSource source(&file);

    Handler handler;
    QXmlSimpleReader reader;
    reader.setContentHandler(&handler);
    reader.setErrorHandler(&handler);

    if (!reader.parse(&source))
    {
        throw std::runtime_error("could not parse file: " + file.fileName().toStdString());
    }

    d.configName = handler["configName"];
    d.description = handler["description"];
    d.baseAddress = handler["baseAddress"].toUInt();
    d.memorySize = handler["memorySize"].toUInt();

    int functionCount = handler["functionCount"].toInt();
    for (int i = 0; i < functionCount; i++)
    {
        QString number = QString("%0").arg(i);
        bool ok;
        d.nativeInterface.append(NativeFunction(
             handler["functionClass_" + number],
             handler["functionDescription_" + number],
             handler["functionID_" + number].toInt(&ok),
             handler["functionName_" + number],
             handler["functionParams_" + number]
        ));
        if (!ok)
            qWarning("failed to parse ID for native function %d", i);
    }
}

QString JVMConfig::configName() const
{
    return d.configName;
}

QString JVMConfig::description() const
{
    return d.description;
}

quint32 JVMConfig::baseAddress() const
{
    return d.baseAddress;
}

quint32 JVMConfig::memorySize() const
{
    return d.memorySize;
}

QList<NativeFunction> JVMConfig::nativeInterface() const
{
    return d.nativeInterface;
}
