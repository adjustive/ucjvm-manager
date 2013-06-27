#ifndef SOURCE_H
#define SOURCE_H

#include <QFileInfo>

class Source
{
public:
    explicit Source(QFileInfo const &file);

    QString name() const;
    QString relativeName(QDir const &path) const;

private:
    QFileInfo file;
};

#endif // SOURCE_H
