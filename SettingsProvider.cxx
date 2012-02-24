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
SettingsProvider * SettingsProvider::getInstance()
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

void SettingsProvider::setDvipngBinary( const QString &path )
{
    m_Settings->setValue( "Compiler/dvipngBinary", path );
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

QString SettingsProvider::dvipngBinary() const
{
    return m_Settings->value( "Compiler/dvipngBinary", QString("")).toString();
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

bool SettingsProvider::valid() const
{
    if( latexBinary().length() > 0 &&
        dvipngBinary().length() > 0 &&
        dvisvgmBinary().length() > 0 )
        return true;
    return false;
}

