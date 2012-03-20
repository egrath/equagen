#include "SvgImage.h"

SvgImage::SvgImage( const QByteArray &content ) : BaseImage( content )
{
}

void SvgImage::setOriginalSource(const OriginalSource &source)
{
    qDebug() << "SvgImage::setOriginalSource";

    QDomDocument document;
    document.setContent( *rawContent(), false );

    QUrl urlEncoder;
    QDomElement metadata = document.createElement( "metadata" );
    QDomElement original = document.createElement( "equagen-sourcecode" );
    original.setAttribute( "X-ORIGIN-TYPE", QString( urlEncoder.toPercentEncoding( source.Type )));
    original.setAttribute( "X-ORIGIN-TEMPLATE", QString( urlEncoder.toPercentEncoding( source.Template )));
    original.setAttribute( "X-ORIGIN-SOURCE",QString( urlEncoder.toPercentEncoding( source.Source )));
    metadata.appendChild( original );
    document.firstChildElement( "svg" ).appendChild( metadata );

    // Save
    delete m_RawContent;
    m_RawContent = new QByteArray();
    QTextStream streamWriter( m_RawContent, QIODevice::WriteOnly );

    document.save( streamWriter, 0 );
    streamWriter.flush();
}

const OriginalSource SvgImage::originalSource() const
{
    OriginalSource source;

    QDomDocument document;
    document.setContent( *rawContent(), false );

    // Search for source element
    QDomNode path = document.namedItem( "svg" ).namedItem( "metadata" ).namedItem( "equagen-sourcecode" );
    QDomElement sourceElement = path.toElement();
    if( ! sourceElement.isNull() )
    {
        QUrl urlDecoder;
        source.Type = urlDecoder.fromPercentEncoding( sourceElement.attribute( "X-ORIGIN-TYPE" ).toUtf8() );
        source.Template = urlDecoder.fromPercentEncoding( sourceElement.attribute( "X-ORIGIN-TEMPLATE" ).toUtf8() );
        source.Source = urlDecoder.fromPercentEncoding( sourceElement.attribute( "X-ORIGIN-SOURCE" ).toUtf8() );
    }

    return source;
}
