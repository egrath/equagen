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

OriginalSource SvgUtils::extractOriginalSource(QDomDocument &document)
{
    QDomNodeList groupNodes = document.elementsByTagName( "g" );
    QDomElement metadata;
    bool foundMetadata = false;
    for( int index = 0; index <= groupNodes.count()-1; index ++ )
    {
        metadata = groupNodes.at( index ).firstChildElement( "metadata" );
        if( metadata.attribute( "creator" ).compare( "equagen" ) == 0 )
        {
            foundMetadata = true;
            break;
        }
    }

    OriginalSource source;
    if( foundMetadata )
        qDebug() << "found metadata";
    else
    {
        qDebug() << "No metadata";
        return source;
    }

    // Decode the values and store it
    QUrl urlDecoder;
    source.Template = urlDecoder.fromPercentEncoding( metadata.firstChildElement( "origin-template" ).text().toUtf8() );
    source.Type = urlDecoder.fromPercentEncoding( metadata.firstChildElement( "origin-type" ).text().toUtf8() );
    source.Source = urlDecoder.fromPercentEncoding( metadata.firstChildElement( "origin-source" ).text().toUtf8() );

    return source;
}
