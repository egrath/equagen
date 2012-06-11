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
    image.setText( "origin-type", QString( urlEncoder.toPercentEncoding( source.Type )));
    image.setText( "origin-template", QString( urlEncoder.toPercentEncoding( source.Template )));
    image.setText( "origin-source", QString( urlEncoder.toPercentEncoding( source.Source )));
    image.setText( "origin-uuid", QString( urlEncoder.toPercentEncoding( source.Uuid )));

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

    source.Type = image.text( "origin-type" );
    source.Template = image.text( "origin-template" );
    source.Source = image.text( "origin-source" );
    source.Uuid = image.text( "origin-uuid" );

    return source;
}
