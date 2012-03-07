#include "SettingsProvider.h"

// Allocate memory for the instance
SettingsProvider *SettingsProvider::m_Instance;

// PRIVATE
SettingsProvider::SettingsProvider()
{
    m_Settings = new QSettings( "egrath", "equagen" );
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

