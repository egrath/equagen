#include "PngImage.h"

PngImage::PngImage( const QByteArray &content ) : BaseImage( content )
{

}

void PngImage::setOriginalSource( const OriginalSource &source )
{
    if( m_RawContent == 0 )
        return;

    // Embed original sourcecode as metadata in PNG Image
    QUrl urlEncoder;
    QImage image = QImage::fromData( *rawContent() );
    image.setText( "X-ORIGIN-TYPE", QString( urlEncoder.toPercentEncoding( source.Type )));
    image.setText( "X-ORIGIN-TEMPLATE", QString( urlEncoder.toPercentEncoding( source.Template )));
    image.setText( "X-ORIGIN-SOURCE", QString( urlEncoder.toPercentEncoding( source.Source )));

    // Save modified image back to Byte array
    delete m_RawContent;
    m_RawContent = new QByteArray();
    QBuffer imageBuffer( m_RawContent );
    imageBuffer.open( QIODevice::WriteOnly );
    image.save( &imageBuffer, "PNG" );
    imageBuffer.close();
}

const OriginalSource PngImage::originalSource() const
{
    OriginalSource source;
    QImage image = QImage::fromData( *rawContent() );

    source.Type = image.text( "X-ORIGIN-TYPE" );
    source.Template = image.text( "X-ORIGIN-TEMPLATE" );
    source.Source = image.text( "X-ORIGIN-SOURCE" );

    return source;
}
