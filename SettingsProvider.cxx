#include "SettingsProvider.h"

// Allocate memory for the instance
SettingsProvider *SettingsProvider::m_Instance;

// PRIVATE
SettingsProvider::SettingsProvider()
{
    m_Settings = new QSettings( "egrath", "equagen" );
    debug() << "Settings path: " << m_Settings->fileName();
}

SettingsProvider::~SettingsProvider()
{
    delete m_Settings;
}

// PUBLIC
SettingsProvider * SettingsProvider::instance()
{
    if( m_Instance == 0 )
        m_Instance = new SettingsProvider();

    return m_Instance;
}

void SettingsProvider::setLatexBinary( const QString &path )
{
    m_Settings->setValue( "Compiler/latexBinary", path );
    m_Settings->sync();
}

void SettingsProvider::setDvisvgmBinary( const QString &path )
{
    m_Settings->setValue( "Compiler/dvisvgmBinary", path );
    m_Settings->sync();
}

QString SettingsProvider::latexBinary() const
{
    return m_Settings->value( "Compiler/latexBinary", QString("")).toString();
}

QString SettingsProvider::dvisvgmBinary() const
{
    return m_Settings->value( "Compiler/dvisvgmBinary", QString("")).toString();
}

// Preview
void SettingsProvider::setPreviewScale( const qreal &scale )
{
    m_Settings->setValue( "Preview/scale", scale );
    m_Settings->sync();
}

qreal SettingsProvider::previewScale() const
{
    return m_Settings->value( "Preview/scale", "1.0" ).toReal();
}

// Editor font
void SettingsProvider::setEditorFont( const QString &family, int pointSize )
{
    m_Settings->setValue( "Editor/fontFamily", family );
    m_Settings->setValue( "Editor/fontSize", pointSize );
    m_Settings->sync();
}

QFont SettingsProvider::editorFont() const
{
    QString fontFamily = m_Settings->value( "Editor/fontFamily", "Monospace" ).toString();
    int fontSize = m_Settings->value( "Editor/fontSize", "10" ).toInt();

    return QFont( fontFamily, fontSize );
}

// Window geometry and state
void SettingsProvider::setWindowGeometry( const QByteArray &geometry )
{
    m_Settings->setValue( "Window/geometry", geometry );
    m_Settings->sync();
}

void SettingsProvider::setWindowState( const QByteArray &state )
{
    m_Settings->setValue( "Window/state", state );
    m_Settings->sync();
}

QByteArray SettingsProvider::windowGeometry() const
{
    return m_Settings->value( "Window/geometry" ).toByteArray();
}

QByteArray SettingsProvider::windowState() const
{
    return m_Settings->value( "Window/state" ).toByteArray();
}

// Templates
void SettingsProvider::addLatexTemplate(const Template &templ)
{
    m_Settings->setValue( QString( "Templates/%1/name" ).arg( templ.uuid().toString() ), templ.name() );
    m_Settings->setValue( QString( "Templates/%1/code" ).arg( templ.uuid().toString() ), templ.code() );
    m_Settings->sync();
}

void SettingsProvider::delLatexTemplate(const Template &templ)
{
    m_Settings->remove( QString( "Templates/%1" ).arg( templ.uuid() ));
    m_Settings->sync();
}

QList<Template *> * SettingsProvider::getLatexTemplates()
{
    debug() << "SettingsProvider::getLatexTemplates()";
    QStringList keys = m_Settings->allKeys();
    QRegExp templateMatcher( "^Templates/\\{[a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12}\\}/.+" );
    QList<Template *> *templates = new QList<Template *>();

    QStringList templateUuids;
    QStringList::iterator iter = keys.begin();
    while( iter != keys.end() )
    {
        QString key = (*iter);
        debug() << "key: " << key;

        if( templateMatcher.exactMatch( key ))
        {
            QString u = key.split( "/" ).at( 1 );
            if( ! templateUuids.contains( u ))
            {
                templateUuids.append(u);
                debug() << "    ---> adding template with uuid" << key.split( "/" ).at(1);
            }
        }
        iter++;
    }

    iter = templateUuids.begin();
    while( iter != templateUuids.end() )
    {
        QString uuid = (*iter);
        QString templateName = m_Settings->value( QString( "Templates/%1/name" ).arg( uuid ), "" ).toString();
        QString templateCode = m_Settings->value( QString( "Templates/%1/code" ).arg( uuid ), "").toString();

        Template *t = new Template( templateName, templateCode, QUuid( uuid ));
        templates->append( t );

        iter++;
    }

    return templates;
}

Template SettingsProvider::getLatexTemplate( const QString &name )
{
    // Special handling for the built-in template
    if( name.compare( "Built-in Template" ) == 0 )
    {
        debug() << "SettingsProvider: Returning default template";

        Template t;
        t.setName( "Built-in Template" );

        QFile defaultTemplate( ":/templates/latex.template" );
        defaultTemplate.open( QFile::ReadOnly );
        t.setCode( QString( defaultTemplate.readAll() ));
        defaultTemplate.close();

        return t;
    }

    QList<Template *> *templates = getLatexTemplates();

    Template templ;
    templ.setName("<UNINITIALIZED>");
    QList<Template *>::iterator iter = templates->begin();
    while( iter != templates->end() )
    {
        Template *t = (Template*) (*iter);
        if( t->name().compare( name ) == 0 )
        {
            templ = *t;
            break;
        }
        iter++;
    }

    // Free
    iter = templates->begin();
    while( iter != templates->end() )
    {
        delete (*iter);
        iter++;
    }
    delete templates;

    return templ;
}

bool SettingsProvider::valid() const
{
    if( latexBinary().length() > 0 &&
        dvisvgmBinary().length() > 0 )
        return true;
    return false;
}

void SettingsProvider::setDirty()
{
    emit configurationSettingsChanged();
}
