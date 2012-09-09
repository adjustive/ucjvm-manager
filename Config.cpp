#include "Config.h"

#include <QXmlSimpleReader>
#include <QDebug>

struct ConfigXmlHandler : QXmlDefaultHandler
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
            qWarning() << "configuration file" << fileName << "contains no such key:" << key;
        return config[key];
    }


    ConfigXmlHandler(QString fileName)
        : fileName(fileName)
    {
    }

private:
    QString fileName;
    QString key;
    QMap<QString, QString> config;
};

Config::Config()
{
}

Config::Config(QString path)
{
    QFile file(path);
    if (!file.open(QFile::ReadOnly))
    {
        qFatal("could not open file: %s", file.fileName().toUtf8().constData());
        return;
    }

    QXmlInputSource source(&file);

    ConfigXmlHandler handler(file.fileName());
    QXmlSimpleReader reader;
    reader.setContentHandler(&handler);
    reader.setErrorHandler(&handler);

    if (!reader.parse(&source))
    {
        qFatal("could not parse file: %s", file.fileName().toUtf8().constData());
        return;
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
        {
            qWarning("failed to parse ID for native function %d", i);
        }
    }
}

QString Config::configName() const
{
    return d.configName;
}

QString Config::description() const
{
    return d.description;
}

quint32 Config::baseAddress() const
{
    return d.baseAddress;
}

quint32 Config::memorySize() const
{
    return d.memorySize;
}

MemoryModel const &Config::memoryModel() const
{
    // TODO: memory models
    return MemoryModel::AVR32;
}

QList<NativeFunction> const &Config::nativeInterface() const
{
    return d.nativeInterface;
}
