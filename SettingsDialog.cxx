#include "SettingsDialog.h"

void SettingsDialog::setupUserInterface()
{
    m_UserInterface = new Ui_SettingsDialog();
    m_UserInterface->setupUi( this );

    // Connect signals
    QObject::connect( m_UserInterface->buttonBrowseLatex, SIGNAL(clicked()), this, SLOT(buttonBrowseLatexPressed()));
    QObject::connect( m_UserInterface->buttonBrowseDvipng, SIGNAL(clicked()), this, SLOT(buttonBrowseDvipngPressed()));
    QObject::connect( m_UserInterface->buttonBrowseDvisvgm, SIGNAL(clicked()),this,SLOT(buttonBrowseDvisvgmPressed()));
    QObject::connect( m_UserInterface->buttonSave,SIGNAL(clicked()),this,SLOT(buttonSavePressed()));
    QObject::connect( m_UserInterface->buttonCancel,SIGNAL(clicked()),this,SLOT(buttonCancelPressed()));
}

void SettingsDialog::buttonBrowseLatexPressed()
{
    qDebug() << "Browse for Latex Binary";

    QString newBinary = showFileOpenDialog( m_UserInterface->textEditLatex->text() );
    if( newBinary.length() > 0 )
        m_UserInterface->textEditLatex->setText( newBinary );
}

void SettingsDialog::buttonBrowseDvipngPressed()
{
    qDebug() << "Browse for DviPng Binary";

    QString newBinary = showFileOpenDialog( m_UserInterface->textEditDvipng->text() );
    if( newBinary.length() > 0 )
        m_UserInterface->textEditDvipng->setText( newBinary );
}

void SettingsDialog::buttonBrowseDvisvgmPressed()
{
    qDebug() << "Browse for DviSvgm Binary";

    QString newBinary = showFileOpenDialog( m_UserInterface->textEditDvisvgm->text() );
    if( newBinary.length() > 0 )
        m_UserInterface->textEditDvisvgm->setText( newBinary );
}

void SettingsDialog::buttonSavePressed()
{
    qDebug() << "Save";

    m_Settings->setLatexBinary( m_UserInterface->textEditLatex->text() );
    m_Settings->setDvipngBinary( m_UserInterface->textEditDvipng->text() );
    m_Settings->setDvisvgmBinary( m_UserInterface->textEditDvisvgm->text() );

    qDebug() << "    latex: " << m_Settings->latexBinary();
    qDebug() << "    dvipng: " << m_Settings->dvipngBinary();
    qDebug() << "    dvisvgm: " << m_Settings->dvisvgmBinary();

    close();
}

void SettingsDialog::buttonCancelPressed()
{
    qDebug() << "Cancel";
    close();
}

QString SettingsDialog::showFileOpenDialog( const QString &directory )
{
    QFileDialog fileDialog;
    fileDialog.setDirectory( directory );
    fileDialog.setFileMode( QFileDialog::ExistingFile );
    fileDialog.setAcceptMode( QFileDialog::AcceptOpen );
    if( fileDialog.exec() )
        return fileDialog.selectedFiles().at( 0 );

    return "";
}

SettingsDialog::SettingsDialog( QWidget *parent ) : QDialog( parent )
{
    setupUserInterface();

    // Fill with values from settings
    m_Settings = SettingsProvider::getInstance();
    m_UserInterface->textEditLatex->setText( m_Settings->latexBinary() );
    m_UserInterface->textEditDvipng->setText( m_Settings->dvipngBinary() );
    m_UserInterface->textEditDvisvgm->setText( m_Settings->dvisvgmBinary() );
}

SettingsDialog::~SettingsDialog()
{
}
