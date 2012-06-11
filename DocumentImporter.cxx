#include "DocumentImporter.h"

// PRIVATE
bool DocumentImporter::parsePng()
{
    qDebug() << "DocumentImporter: Parsing PNG";

    QImage *img;
    if( m_ImportType == IT_FILE )
        img = new QImage( m_File );
    else
    {
        const QMimeData *mime = QApplication::clipboard()->mimeData();
        if( mime->hasFormat( "image/png" ))
            img = new QImage( QImage::fromData( mime->data( "image/png" )));
        else
        {
            qDebug() << "Failed to parse Image data from clipboard";
            return false;
        }
    }

    QUrl urlDecoder;
    m_Source.Type = urlDecoder.fromPercentEncoding( img->text( "origin-type" ).toUtf8() );
    m_Source.Template = urlDecoder.fromPercentEncoding( img->text( "origin-template" ).toUtf8() );
    m_Source.Source = urlDecoder.fromPercentEncoding( img->text( "origin-source" ).toUtf8() );

    delete img;

    if( m_Source.Type.isEmpty() || m_Source.Template.isEmpty() || m_Source.Source.isEmpty() )
        return false;
    else
        return true;
}

bool DocumentImporter::parseSvg()
{
    qDebug() << "DocumentImporter: Parsing SVG";

    QDomDocument document;

    if( m_ImportType == IT_FILE )
    {
        QFile inputFile( m_File );
        inputFile.open( QFile::ReadOnly );

        // Build DOM representation of SVG
        document.setContent( inputFile.readAll() );
        inputFile.close();
    }
    else if( m_ImportType == IT_CLIPBOARD )
    {
        const QMimeData *mime = QApplication::clipboard()->mimeData();
        if( mime->hasFormat( "image/svg+xml" ))
            document.setContent( mime->data( "image/svg+xml" ));
        else
        {
            qDebug() << "Failed to get SVG from clipboard";
            return false;
        }
    }

    // Extract source from metadata in SVG DOM
    m_Source = SvgUtils::extractOriginalSource( document );

    // Check if everything went good
    if( m_Source.Type.isEmpty() || m_Source.Template.isEmpty() || m_Source.Source.isEmpty() )
        return false;
    else
        return true;
}

// PUBLIC
// Constructor for import from Clipboard
DocumentImporter::DocumentImporter()
{
    qDebug() << "DocumentImporter: Importing from Clipboard";
    m_File = "CLIPBOARD";
    m_ImportType = IT_CLIPBOARD;
}

// Constructor for import from File
DocumentImporter::DocumentImporter(const QString &fileName)
{
    qDebug() << "DocumentImporter: Importing from File";
    m_ImportType = IT_FILE;
    m_File = fileName;
}

bool DocumentImporter::isValid() const
{
    return m_IsValid;
}

bool DocumentImporter::parse()
{
    m_IsValid = false;
    if( m_ImportType == IT_FILE )
    {
        if( m_File.toLower().endsWith( ".png" ))
            m_IsValid = parsePng();
        else if( m_File.toLower().endsWith( ".svg" ))
            m_IsValid = parseSvg();
    } else if( m_ImportType == IT_CLIPBOARD )
    {
        // Check if there is a SVG or PNG in the clipboard
        const QMimeData *mime = QApplication::clipboard()->mimeData();
        if( mime->hasFormat( "image/svg+xml" ))
            m_IsValid = parseSvg();
        else if( mime->hasFormat( "image/png" ))
            m_IsValid = parsePng();
        else
            qDebug() << "Invalid mime format in clipboard";
    }

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

const QString & DocumentImporter::fileName() const
{
    return m_File;
}
