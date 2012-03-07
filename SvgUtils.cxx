#include "SvgUtils.h"

QByteArray * SvgUtils::rasterSvgToPng( const QByteArray &data, qreal scale )
{
    qDebug() << "SvgUtils::rasterSvgToPng with scale " << scale;

    QSvgRenderer renderer( data );
    QImage image( QSize( renderer.viewBoxF().width() * scale + 4, renderer.viewBoxF().height() * scale + 4 ),
                  QImage::Format_ARGB32 );

    QPainter painter( &image );

    // Draw white background and Render SVG
    painter.fillRect( image.rect(), Qt::white );
    renderer.render( &painter, QRectF( 2, 2, renderer.viewBoxF().width(), renderer.viewBoxF().height() ));

    // Extract raw data from Image
    QByteArray *raw = new QByteArray();
    QBuffer imageBuffer( raw );
    imageBuffer.open( QIODevice::WriteOnly );
    image.save( &imageBuffer, "PNG" );
    imageBuffer.close();

    return raw;
}
