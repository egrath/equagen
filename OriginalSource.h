#ifndef ORIGINALSOURCE_H
#define ORIGINALSOURCE_H

#include <QString>

#include "Debug.h"

struct OriginalSource
{
public:
    QString Type;
    QString Template;
    QString Source;
    QString Uuid;
};
#endif // ORIGINALSOURCE_H
