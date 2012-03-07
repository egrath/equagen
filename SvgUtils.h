#ifndef SVGUTILS_H
#define SVGUTILS_H

#include <QImage>
#include <QtSvg>

class SvgUtils
{
public:
    static QByteArray * rasterSvgToPng( const QByteArray &data, qreal scale = 1.0 );
};


#endif // SVGUTILS_H
