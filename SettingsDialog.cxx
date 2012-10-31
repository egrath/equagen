#include "SettingsDialog.h"

void SettingsDialog::setupUserInterface()
{
    m_UserInterface = new Ui_SettingsDialog();
    m_UserInterface->setupUi( this );

    // Set up font tab
    setupFontTab();

    // Refresh the list of installed templates
    refreshTemplateList();

    // Connect signals
    QObject::connect( m_UserInterface->buttonBrowseLatex, SIGNAL(clicked()), this, SLOT(buttonBrowseLatexPressed()));
    QObject::connect( m_UserInterface->buttonBrowseDvisvgm, SIGNAL(clicked()),this,SLOT(buttonBrowseDvisvgmPressed()));
    QObject::connect( m_UserInterface->buttonSave,SIGNAL(clicked()),this,SLOT(buttonSavePressed()));
    QObject::connect( m_UserInterface->buttonCancel,SIGNAL(clicked()),this,SLOT(buttonCancelPressed()));
    QObject::connect( m_UserInterface->buttonTextColor, SIGNAL( clicked() ),this,SLOT(buttonTextColorPressed()));
    QObject::connect( m_UserInterface->buttonBackgroundColor, SIGNAL(clicked()),this,SLOT(buttonBackgroundColorPressed()));
    QObject::connect( m_UserInterface->buttonTemplateNew, SIGNAL(clicked()), this, SLOT(buttonTemplateNewPressed()));
    QObject::connect( m_UserInterface->buttonTemplateEdit, SIGNAL(clicked()), this, SLOT(buttonTemplateEditPressed()));
    QObject::connect( m_UserInterface->buttonTemplateDelete,SIGNAL(clicked()), this,SLOT(buttonTemplateRemovePressed()));
    QObject::connect( m_UserInterface->templateList,SIGNAL(itemSelectionChanged()),this,SLOT(templateListSelectionChanged()));
}

void SettingsDialog::setupFontTab()
{
    QFontDatabase fdb;
    QStringList fontFamiliesList = fdb.families( QFontDatabase::Latin );

    QString configuredFontFamily = m_Settings->editorFont().family();
    int configuredFontSize = m_Settings->editorFont().pointSize();

    // Add Font Families to Combo
    QStringList::iterator fontFamiliesListIterator = fontFamiliesList.begin();
    while( fontFamiliesListIterator != fontFamiliesList.end() )
    {
        QString currentFontFamily = *( fontFamiliesListIterator );
        m_UserInterface->comboBoxFontFamily->addItem(  currentFontFamily );

        // Is this font the configured one?
        if( currentFontFamily.compare( configuredFontFamily ) == 0 )
            m_UserInterface->comboBoxFontFamily->setCurrentIndex( m_UserInterface->comboBoxFontFamily->count()-1 );

        fontFamiliesListIterator ++;
    }

    // Add standard Font sizes to Combo
    QList<int> fontSizes = QFontDatabase::standardSizes();
    QList<int>::iterator fontSizesIterator = fontSizes.begin();
    while( fontSizesIterator != fontSizes.end() )
    {
        int currentFontSize = *(fontSizesIterator);

        m_UserInterface->comboBoxFontSize->addItem( QString( "%1" ).arg( currentFontSize ));

        // Current font size equal the configured one?
        if( currentFontSize == configuredFontSize )
            m_UserInterface->comboBoxFontSize->setCurrentIndex( m_UserInterface->comboBoxFontSize->count() -1 );

        fontSizesIterator++;
    }
}

void SettingsDialog::refreshTemplateList()
{
    QListWidget *templateList = m_UserInterface->templateList;
    templateList->clear();

    QList<Template *> *templates = m_Settings->getLatexTemplates();
    QList<Template *>::iterator iter = templates->begin();

    while( iter != templates->end() )
    {
        qDebug() << "SettingsDialog: Adding Template to list:" << (*iter)->text();
        templateList->addItem( (*iter));
        iter++;
    }

    delete templates;
}

void SettingsDialog::buttonTemplateNewPressed()
{
    qDebug() << "Showing Template Editor with empty template";

    TemplateEditor *templateEditor = new TemplateEditor();

    int rc = templateEditor->exec();
    if( rc == QDialog::Accepted )
    {
        Template *t = new Template(
                    templateEditor->templateName(),
                    templateEditor->templateCode());

        m_Settings->addLatexTemplate( *t );
        refreshTemplateList();
    }

    delete templateEditor;
}

void SettingsDialog::buttonTemplateEditPressed()
{
    qDebug() << "Editing template";

    QListWidget *templateList = m_UserInterface->templateList;
    Template *t = ( Template * ) templateList->selectedItems().at(0);

    TemplateEditor *templateEditor = new TemplateEditor();
    templateEditor->setTemplateName( t->name() );
    templateEditor->setTemplateCode( t->code() );

    int rc = templateEditor->exec();
    if( rc == QDialog::Accepted )
    {
        t->setName( templateEditor->templateName() );
        t->setCode( templateEditor->templateCode() );

        // This will also perform the update
        m_Settings->addLatexTemplate( *t );
        refreshTemplateList();
    }

    delete templateEditor;
}

void SettingsDialog::buttonTemplateRemovePressed()
{
    Template *t = ( Template *) m_UserInterface->templateList->selectedItems().at( 0 );
    qDebug() << "Removing template: " << t->name();

    m_Settings->delLatexTemplate( *t );
    refreshTemplateList();
}

void SettingsDialog::buttonBrowseLatexPressed()
{
    qDebug() << "Browse for Latex Binary";

    QString newBinary = showFileOpenDialog( m_UserInterface->textEditLatex->text() );
    if( newBinary.length() > 0 )
        m_UserInterface->textEditLatex->setText( newBinary );
}

void SettingsDialog::buttonBrowseDvisvgmPressed()
{
    qDebug() << "Browse for DviSvgm Binary";

    QString newBinary = showFileOpenDialog( m_UserInterface->textEditDvisvgm->text() );
    if( newBinary.length() > 0 )
        m_UserInterface->textEditDvisvgm->setText( newBinary );
}

void SettingsDialog::buttonTextColorPressed()
{
    qDebug() << "SettingsDialog: buttonTextColorPressed";
}

void SettingsDialog::buttonBackgroundColorPressed()
{
    qDebug() << "SettingsDialog: buttonBackgroundColorPressed";
}

void SettingsDialog::buttonSavePressed()
{
    qDebug() << "Save";

    m_Settings->setLatexBinary( m_UserInterface->textEditLatex->text() );
    m_Settings->setDvisvgmBinary( m_UserInterface->textEditDvisvgm->text() );
    m_Settings->setEditorFont( m_UserInterface->comboBoxFontFamily->itemText( m_UserInterface->comboBoxFontFamily->currentIndex() ),
                               m_UserInterface->comboBoxFontSize->itemText( m_UserInterface->comboBoxFontSize->currentIndex() ).toInt() );


    qDebug() << "    latex: " << m_Settings->latexBinary();
    qDebug() << "    dvisvgm: " << m_Settings->dvisvgmBinary();   
    qDebug() << "    font: " << m_Settings->editorFont();

    // Set dirty, so that the corresponding signal is emitted and all subscribers
    // change their settings according to the new values
    m_Settings->setDirty();

    close();
}

void SettingsDialog::buttonCancelPressed()
{
    qDebug() << "Cancel";
    close();
}

void SettingsDialog::templateListSelectionChanged()
{
    if( m_UserInterface->templateList->selectedItems().count() > 0 )
    {
        m_UserInterface->buttonTemplateDelete->setEnabled(true);
        m_UserInterface->buttonTemplateEdit->setEnabled(true);
    }
    else
    {
        m_UserInterface->buttonTemplateDelete->setEnabled(false);
        m_UserInterface->buttonTemplateEdit->setEnabled(false);
    }
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
    // Get settings Object
    m_Settings = SettingsProvider::instance();
    setupUserInterface();

    // Fill with values from settings    
    m_UserInterface->textEditLatex->setText( m_Settings->latexBinary() );
    m_UserInterface->textEditDvisvgm->setText( m_Settings->dvisvgmBinary() );
}

SettingsDialog::~SettingsDialog()
{
}
