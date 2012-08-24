#ifndef NATIVEFUNCTION_H
#define NATIVEFUNCTION_H

#include <QString>

struct NativeFunction
{
    NativeFunction(QString className,
                   QString description,
                   QString id,
                   QString name,
                   QString params);

    QString className;
    QString description;
    QString id;
    QString name;
    QString params;
};

#endif // NATIVEFUNCTION_H
