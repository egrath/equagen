#include "SvgImage.h"

SvgImage::SvgImage( const QByteArray &content ) : BaseImage( content )
{
}

void SvgImage::setOriginalSource(const OriginalSource &source)
{
    qDebug() << "SvgImage::setOriginalSource";

    QDomDocument document;
    document.setContent( *rawContent(), false );

    QDomElement metadata = document.createElement( "metadata" );
    QDomElement original = document.createElement( "equagen-sourcecode" );
    original.setAttribute( "X-ORIGIN-TYPE", source.Type );
    original.setAttribute( "X-ORIGIN-TEMPLATE", source.Template );
    original.setAttribute( "X-ORIGIN-SOURCE", source.Source );
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
        source.Type = sourceElement.attribute( "X-ORIGIN-TYPE" );
        source.Template = sourceElement.attribute( "X-ORIGIN-TEMPLATE" );
        source.Source = sourceElement.attribute( "X-ORIGIN-SOURCE" );
    }

    return source;
}
