#ifndef SVGUTILS_H
#define SVGUTILS_H

#include <QImage>
#include <QtSvg>
#include <QDomDocument>

#include "OriginalSource.h"

class SvgUtils
{
public:
    static QByteArray * rasterSvgToPng( const QByteArray &data, qreal scale = 1.0 );
    static OriginalSource extractOriginalSource( QDomDocument &document );
};


#endif // SVGUTILS_H
