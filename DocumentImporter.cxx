#include "DocumentImporter.h"

// PRIVATE
bool DocumentImporter::parsePng()
{
    qDebug() << "DocumentImporter: Parsing PNG";

    QImage img( m_File );

    QUrl urlDecoder;
    m_Source.Type = urlDecoder.fromPercentEncoding( img.text( "X-ORIGIN-TYPE" ).toUtf8() );
    m_Source.Template = urlDecoder.fromPercentEncoding( img.text( "X-ORIGIN-TEMPLATE" ).toUtf8() );
    m_Source.Source = urlDecoder.fromPercentEncoding( img.text( "X-ORIGIN-SOURCE" ).toUtf8() );

    if( m_Source.Type.isEmpty() || m_Source.Template.isEmpty() || m_Source.Source.isEmpty() )
        return false;
    else
        return true;
}

bool DocumentImporter::parseSvg()
{
    qDebug() << "DocumentImporter: Parsing SVG";

    QFile inputFile( m_File );
    inputFile.open( QFile::ReadOnly );

    QDomDocument document;
    document.setContent( inputFile.readAll() );
    inputFile.close();

    // Search for source element
    QDomNode path = document.namedItem( "svg" ).namedItem( "metadata" ).namedItem( "equagen-sourcecode" );
    QDomElement sourceElement = path.toElement();
    if( ! sourceElement.isNull() )
    {
        QUrl urlDecoder;
        m_Source.Type = urlDecoder.fromPercentEncoding( sourceElement.attribute( "X-ORIGIN-TYPE" ).toUtf8() );
        m_Source.Template = urlDecoder.fromPercentEncoding( sourceElement.attribute( "X-ORIGIN-TEMPLATE" ).toUtf8() );
        m_Source.Source = urlDecoder.fromPercentEncoding( sourceElement.attribute( "X-ORIGIN-SOURCE" ).toUtf8() );
    }

    if( m_Source.Type.isEmpty() || m_Source.Template.isEmpty() || m_Source.Source.isEmpty() )
        return false;
    else
        return true;
}

// PUBLIC
DocumentImporter::DocumentImporter(const QString &fileName)
{
    m_File = fileName;
}

bool DocumentImporter::isValid() const
{
    return m_IsValid;
}

bool DocumentImporter::parse()
{
    m_IsValid = false;
    if( m_File.toLower().endsWith( ".png" ))
        m_IsValid = parsePng();
    else if( m_File.toLower().endsWith( ".svg" ))
        m_IsValid = parseSvg();

    return m_IsValid;
}

DocumentType DocumentImporter::type() const
{
    if( isValid() )
    {
        if( m_Source.Type == "latex" )
            return DT_LATEX;
        else if( m_Source.Type == "sketch" )
            return DT_SKETCH;
    }

    return DT_INVALID;
}

const OriginalSource & DocumentImporter::source() const
{
    return m_Source;
}
