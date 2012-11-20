#include "TemplateEditor.h"

// PRIVATE
void TemplateEditor::setupUserInterface()
{
    m_UserInterface = new Ui_TemplateEditor();
    m_UserInterface->setupUi( this );

    // Connect signals
    QObject::connect( m_UserInterface->buttonCancel, SIGNAL(clicked()), this, SLOT( buttonCancelPressed()));
    QObject::connect( m_UserInterface->buttonSaveExit, SIGNAL(clicked()), this, SLOT(buttonSaveAndExitPressed()));
    QObject::connect( m_UserInterface->buttonLoadDefault, SIGNAL(clicked()), this, SLOT(buttonLoadDefaultPressed()));
}

// PRIVATE SLOTS
void TemplateEditor::buttonCancelPressed()
{
    setResult( QDialog::Rejected );
    reject();
}

void TemplateEditor::buttonSaveAndExitPressed()
{
    if( m_UserInterface->lineEditTemplateName->text().length() <= 0 )
    {
        QMessageBox msgBox( QMessageBox::Critical, "Error", "Template name must not be empty", QMessageBox::Ok, this );
        msgBox.exec();
    } else
    {
        QString thisTemplateName = m_UserInterface->lineEditTemplateName->text();
        Template t = m_Settings->getLatexTemplate( thisTemplateName );
        if( t.name().compare( "<UNINITIALIZED>" ) == 0 )
        {
            setResult( QDialog::Accepted );
            accept();
        }
        else if( t.name().compare( thisTemplateName ) == 0 && m_EditExisting )
        {
            setResult( QDialog::Accepted );
            accept();
        }
        else
        {            
            QMessageBox msgBox( QMessageBox::Critical, "Error", "Template name already exist, choose another one", QMessageBox::Ok, this );
            msgBox.exec();
        }
    }
}

void TemplateEditor::buttonLoadDefaultPressed()
{
    debug() << "Loading default LaTeX template into editor";

    QFile defaultTemplate( ":/templates/latex.template" );
    defaultTemplate.open( QFile::ReadOnly );

    debug() << defaultTemplate.size();
    m_UserInterface->textEditCode->setPlainText( QString( defaultTemplate.readAll() ));

    defaultTemplate.close();
}

// PUBLIC
TemplateEditor::TemplateEditor( QWidget *parent, bool editExisting ) : QDialog( parent )
{
    m_Settings = SettingsProvider::instance();
    m_EditExisting = editExisting;
    setupUserInterface();
}

TemplateEditor::~TemplateEditor()
{
    delete m_UserInterface;
}

void TemplateEditor::setTemplateName( const QString &name )
{
    m_UserInterface->lineEditTemplateName->setText( name );
}

void TemplateEditor::setTemplateCode( const QString &code )
{
    m_UserInterface->textEditCode->setPlainText( code );
}

QString TemplateEditor::templateName() const
{
    return m_UserInterface->lineEditTemplateName->text();
}

QString TemplateEditor::templateCode() const
{
    return m_UserInterface->textEditCode->document()->toPlainText();
}


