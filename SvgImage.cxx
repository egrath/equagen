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

    // Build the Metadata Element and it's childs
    QDomElement description = document.createElement( "metadata" );
    description.setAttribute( "creator", "equagen" );
    description.setAttribute( "id", "origin" );

    QDomElement originType = document.createElement( "origin-type" );
    originType.setAttribute( "id", "origin-type" );
    originType.appendChild( document.createTextNode( QString( urlEncoder.toPercentEncoding( source.Type ))));

    QDomElement originTemplate = document.createElement( "origin-template" );
    originTemplate.setAttribute( "id", "origin-template" );
    originTemplate.appendChild( document.createTextNode( QString( urlEncoder.toPercentEncoding( source.Template ))));

    QDomElement originSource = document.createElement( "origin-source" );
    originSource.setAttribute( "id", "origin-source" );
    originSource.appendChild( document.createTextNode( QString( urlEncoder.toPercentEncoding( source.Source ))));

    QDomElement originUuid = document.createElement( "origin-uuid" );
    originUuid.setAttribute( "id", "origin-uuid" );
    originUuid.appendChild( document.createTextNode( QString( urlEncoder.toPercentEncoding( source.Uuid ))));

    // Append Nodes to Description Element
    description.appendChild( originType );
    description.appendChild( originTemplate );
    description.appendChild( originSource );
    description.appendChild( originUuid );

    // Append the complete Description Node to the group Element
    QDomNode group = document.elementsByTagName( "g" ).at( 0 );
    if( group.hasAttributes() &&
        group.attributes().item( 0 ).toAttr().name().compare( "id" ) == 0 &&
        group.attributes().item( 0 ).toAttr().value().compare( "page1") == 0 )
    {
        group.appendChild( description );
    }

    // Save
    delete m_RawContent;
    m_RawContent = new QByteArray();
    QTextStream streamWriter( m_RawContent, QIODevice::WriteOnly );

    document.save( streamWriter, 0 );
    streamWriter.flush();
}

const OriginalSource SvgImage::originalSource() const
{
    QDomDocument document;
    document.setContent( *rawContent(), false );

    return SvgUtils::extractOriginalSource( document );
}
