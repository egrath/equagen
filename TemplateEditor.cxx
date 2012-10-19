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
        setResult( QDialog::Accepted );
        accept();
    }
}

void TemplateEditor::buttonLoadDefaultPressed()
{
    qDebug() << "Loading default LaTeX template into editor";

    QFile defaultTemplate( ":/templates/latex.template" );
    defaultTemplate.open( QFile::ReadOnly );

    qDebug() << defaultTemplate.size();
    m_UserInterface->textEditCode->setPlainText( QString( defaultTemplate.readAll() ));

    defaultTemplate.close();
}

// PUBLIC
TemplateEditor::TemplateEditor( QWidget *parent) : QDialog( parent )
{
    setupUserInterface();
}

TemplateEditor::~TemplateEditor()
{
    delete m_UserInterface;
}

QString TemplateEditor::templateName() const
{
    return m_UserInterface->lineEditTemplateName->text();
}

QString TemplateEditor::templateCode() const
{
    return m_UserInterface->textEditCode->document()->toPlainText();
}


