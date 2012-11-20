#include "PlainTextEditor.h"

void PlainTextEditor::configurationSettingsChanged()
{
    debug() << "PlainTextEditor: configuation settings changed";

    // We are only interested in the font
    setFont( m_Settings->editorFont() );
}

PlainTextEditor::PlainTextEditor( QWidget *parent ) : QPlainTextEdit( parent )
{
    debug() << "PlainTextEditor::ctor";

    m_Settings = SettingsProvider::instance();
    QObject::connect( m_Settings, SIGNAL(configurationSettingsChanged()), this, SLOT(configurationSettingsChanged()));

    // Set font to configured one
    setFont( m_Settings->editorFont() );
}

PlainTextEditor::~PlainTextEditor()
{
}

