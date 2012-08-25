#include "NativeFunction.h"

NativeFunction::NativeFunction(QString className,
                               QString description,
                               quint16 id,
                               QString name,
                               QString params)
    : className(className)
    , description(description)
    , id(id)
    , name(name)
    , params(params)
{
}


bool NativeFunction::matches(QString className, QString name, QString params) const
{
    return this->className == className &&
           this->name == name &&
           this->params == params;
}
