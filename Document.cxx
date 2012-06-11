#include "Document.h"

// PROTECTED
void Document::setLastCompileError( const QString &error )
{
    m_LastCompileErrorMessage = error;
}

void Document::setDocumentValid( bool valid )
{
    m_Valid = valid;
}

void Document::setDocumentType( DocumentType type )
{
    m_DocType = type;
}

SettingsProvider * Document::settingsProvider()
{
    return m_Settings;
}

// PUBLIC
Document::Document( const QString &name, const QString &initial )
{
    setPlainContent( initial );
    setName( name );

    m_Svg = 0;
    m_Png = 0;
    setDocumentValid( false );
    m_Settings = SettingsProvider::instance();

    // Generate a uuid for this document
    m_Uuid = QUuid::createUuid();
    qDebug() << "Document with Name: " << name << " has the UUID: " << m_Uuid.toString();

    // Set document to invalid type initially
    setDocumentType( DT_INVALID );
}

Document::~Document()
{
}

void Document::setPlainContent( const QString &content )
{
    m_PlainContent = content;

    qDebug() << "Document::setPlainContent";
}

const QString & Document::plainContent() const
{
    return m_PlainContent;
}

void Document::setName( const QString &name )
{
    m_Name = name;
}

const QString & Document::name() const
{
    return m_Name;
}

const QString & Document::lastCompileError() const
{
    return m_LastCompileErrorMessage;
}

const PngImage & Document::pngImage() const
{
    return *m_Png;
}

const SvgImage & Document::svgImage() const
{
    return *m_Svg;
}

void Document::setUuid( const QUuid &uuid )
{
    m_Uuid = uuid;
    qDebug() << "Document with Name [" << m_Name << "] changed it's UUID to: " << m_Uuid;
}

const QUuid & Document::uuid() const
{
    return m_Uuid;
}

bool Document::documentValid() const
{
    return m_Valid;
}

const DocumentType & Document::documentType() const
{
    return m_DocType;
}
