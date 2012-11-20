#include "MainWindow.h"

void MainWindow::setupUserInterface()
{    
    m_UserInterface = new Ui_MainWindow();
    m_UserInterface->setupUi( this );

    // Set the Window icon
    setWindowIcon( QIcon( QPixmap::fromImage( QImage( ":/icons/applogo.png" ))));

    // Create Label for Status messages
    m_StatusLabel = new QLabel( "", m_UserInterface->statusbar );
    m_UserInterface->statusbar->addWidget( m_StatusLabel );

    // Connect signals
    QObject::connect( m_UserInterface->actionButtonCompile, SIGNAL(triggered(bool)), this, SLOT(buttonCompilePressed(bool)));
    QObject::connect( m_UserInterface->actionButtonErrorLog,SIGNAL(triggered(bool)),this,SLOT(buttonErrorLogPressed(bool)));
    QObject::connect( m_UserInterface->actionButtonCopyClipboard,SIGNAL(triggered(bool)),this,SLOT(buttonCopyClipboardPressed(bool)));
    QObject::connect( m_UserInterface->tabWidget, SIGNAL(currentChanged(int)),this,SLOT(tabWidgetIndexChanged(int)));
    QObject::connect( m_UserInterface->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(tabCloseRequested(int)));

    // Connect Edit menu
    QObject::connect( m_UserInterface->actionEditOptions, SIGNAL( triggered( bool )), this, SLOT( menuEditOptionsPressed(bool)));
    QObject::connect( m_UserInterface->actionEditCopy, SIGNAL(triggered(bool)), this, SLOT( buttonCopyClipboardPressed(bool)));
    QObject::connect( m_UserInterface->actionEditPaste, SIGNAL(triggered(bool)), this, SLOT(menuEditPastePressed(bool)));

    // Connect File Menu
    QObject::connect( m_UserInterface->actionFileQuit, SIGNAL( triggered( bool )), this, SLOT( menuFileQuitPressed(bool)));
    QObject::connect( m_UserInterface->actionFileExportPng, SIGNAL(triggered(bool)), this, SLOT(menuFileExportPngPressed(bool)));
    QObject::connect( m_UserInterface->actionFileExportSvg, SIGNAL(triggered(bool)), this, SLOT(menuFileExportSvgPressed(bool)));
    QObject::connect( m_UserInterface->actionFileImport, SIGNAL( triggered( bool )), this, SLOT( menuFileImportPressed(bool)));

    // Connect View Items
    QObject::connect( m_UserInterface->actionViewZoomIn, SIGNAL( triggered( bool )), this, SLOT( menuViewZoomInPressed(bool)));
    QObject::connect( m_UserInterface->actionViewZoomOut, SIGNAL(triggered(bool)), this, SLOT(menuViewZoomOutPressed(bool)));
    QObject::connect( m_UserInterface->actionViewNormalSize, SIGNAL( triggered(bool)),this,SLOT(menuViewZoomOriginalPressed(bool)));

    // Connect About menu
    QObject::connect( m_UserInterface->actionHelpAbout, SIGNAL( triggered( bool )), this, SLOT( menuHelpAboutPressed(bool)));

    // Set shortcut context
    m_UserInterface->actionEditCopy->setShortcut( QKeySequence::Copy );
    m_UserInterface->actionEditCopy->setShortcutContext( Qt::ApplicationShortcut );

    m_UserInterface->actionEditPaste->setShortcut( QKeySequence::Paste );
    m_UserInterface->actionEditPaste->setShortcutContext( Qt::ApplicationShortcut );

    // Build the Toolbar
    setupToolbar();
}

// Create the toolbar (we can't create it in the designer)
void MainWindow::setupToolbar()
{
    // TODO: Implement, currently only non-functional

    // Add Template selector
    QLabel *templateSelectorLabel = new QLabel( "Template" );
    m_TemplateSelectorComboBox = new QComboBox();
    m_UserInterface->toolBar->addSeparator();
    m_UserInterface->toolBar->addWidget( templateSelectorLabel );
    m_UserInterface->toolBar->addWidget( m_TemplateSelectorComboBox );
    setupTemplateList();
    QObject::connect( m_TemplateSelectorComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(toolbarTemplateSelectorIndexChanged(QString)));

    // Add PNG/SVG Copy Mode selector
    QLabel *copySelectorLabel = new QLabel( "Clipboard type" );
    m_CopySelectorComboBox = new QComboBox();
    m_CopySelectorComboBox->addItem( "PNG" );
    m_CopySelectorComboBox->addItem( "SVG" );
    m_CopySelectorComboBox->addItem( "Code" );
    m_CopySelectorComboBox->setCurrentIndex( 1 );
    m_UserInterface->toolBar->addSeparator();
    m_UserInterface->toolBar->addWidget( copySelectorLabel );
    m_UserInterface->toolBar->addWidget( m_CopySelectorComboBox );

    // Connect
    QObject::connect( m_CopySelectorComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(toolbarCopyModeSelectorIndexChanged(QString)));
}

void MainWindow::setupTemplateList()
{
    // Add the default template
    m_TemplateSelectorComboBox->clear();
    m_TemplateSelectorComboBox->addItem( "Built-in Template" );
    m_TemplateSelectorComboBox->setCurrentIndex( 0 );

    // Add all other templates
    QList<Template *> *templates = m_Settings->getLatexTemplates();
    QList<Template *>::iterator iter = templates->begin();
    while( iter != templates->end() )
    {
        Template *t = (*iter);
        m_TemplateSelectorComboBox->addItem( t->name(), QVariant::fromValue(*t));
        iter ++;
    }

    // Free Templates
    iter = templates->begin();
    while( iter != templates->end() )
    {
        delete (*iter);
        iter++;
    }
    delete templates;
}

void MainWindow::switchToDocument( const QUuid &uuid )
{
    QTabWidget *tw = m_UserInterface->tabWidget;

    DocumentEditor *editor;
    for( int index = 0; index < tw->count(); index ++ )
    {
        editor = ( DocumentEditor * ) tw->widget( index );
        if( editor->uuid() == uuid )
        {
            debug() << "We already have the document with UUID open, switching to it.";
            tw->setCurrentIndex( index );
            break;
        }
    }
}

// Return the DocumentEditor for the given UUID if it's open
DocumentEditor * MainWindow::getDocumentTabForUuid( const QUuid &uuid )
{
    QTabWidget *tw = m_UserInterface->tabWidget;

    DocumentEditor *editor;
    for( int index = 0; index < tw->count(); index ++ )
    {
        editor = ( DocumentEditor * ) tw->widget( index );
        if( editor->uuid() == uuid )
            return editor;
    }

    return 0;
}

// Insert a new Document Editor Tab
DocumentEditor * MainWindow::addDocumentTab( DocumentType type, const QString &name )
{
    debug() << "MainWindow::addDocumentTab";

    QTabWidget *tw = m_UserInterface->tabWidget;

    // Build Tab content
    DocumentEditor *editor = new DocumentEditor( type, name );

    // Load icon for tab
    QIcon tabIcon;
    if( type == DT_LATEX )
        tabIcon = QIcon( ":/icons/latex-symbol.svg" );
    else if( type == DT_SKETCH )
        tabIcon = QIcon( ":/icons/sketch-symbol.svg" );

    // Append to Tab Widget
    int tabIndex = tw->count();
    debug() << QString( "    Adding new Tab with Name %1 and ID %2" ).arg( name ).arg( tabIndex );
    tw->insertTab( tabIndex, editor, tabIcon, name );

    // Switch to this Tab
    tw->setCurrentIndex( tabIndex );

    // Tell Document Editor's input widget to take the focus
    editor->setFocus( Qt::TabFocusReason );

    return editor;
}

void MainWindow::addAdderTab()
{
    QTabWidget *tw = m_UserInterface->tabWidget;
    QPushButton *addDocumentButton = new QPushButton( QIcon( ":/icons/list-add.svg" ), "" );

    QMenu *addDocumentMenu = new QMenu( addDocumentButton );
    QAction *addLatexDocumentTabAction = addDocumentMenu->addAction( "LaTeX Document" );
    QAction *addSketchDocumentTabAction = addDocumentMenu->addAction( "Sketch Document" );
    addSketchDocumentTabAction->setEnabled( false );

    QObject::connect( addLatexDocumentTabAction, SIGNAL(triggered()), this, SLOT(menuAddLatexDocumentPressed()));
    QObject::connect( addSketchDocumentTabAction, SIGNAL( triggered() ), this, SLOT(menuAddSketchDocumentPressed()));

    addDocumentButton->setMenu( addDocumentMenu );

    tw->setCornerWidget( addDocumentButton, Qt::TopLeftCorner );
}

QString MainWindow::generateEmptyTabName()
{
    return QString( "Untitled-%1" ).arg( m_TabCounter++ );
}

bool MainWindow::exportCurrentDocument( ImageType type )
{
    debug() << "MainWindow: Exporting ...";

    static QString previousFolder = QDir( QDir::currentPath() ).dirName();
    QFileDialog saveAsDialog( this );
    saveAsDialog.setAcceptMode( QFileDialog::AcceptSave );
    saveAsDialog.setDirectory( previousFolder );

    if( type == IT_SVG )
    {
        saveAsDialog.setWindowTitle( "Export as SVG" );
        saveAsDialog.setNameFilter( "Scalable Vector Graphics (*.svg)" );

    }
    else if( type == IT_PNG )
    {
        saveAsDialog.setWindowTitle( "Export as PNG" );
        saveAsDialog.setNameFilter( "Portable Network Graphics (*.png)" );
    }

    if( saveAsDialog.exec() == QFileDialog::Accepted )
    {
        QString fileName = saveAsDialog.selectedFiles().at( 0 );
        previousFolder = QDir( fileName ).path();

        // Check if the user has appended the suffix
        if( type == IT_SVG && ! fileName.endsWith( ".svg", Qt::CaseInsensitive ))
            fileName.append( ".svg" );
        else if( type == IT_PNG && ! fileName.endsWith( ".png", Qt::CaseInsensitive ))
            fileName.append( ".png" );

        m_ActiveDocument->exportDocumentToFile( type, fileName );
    }

    return false;
}

bool MainWindow::importDocument( DocumentImporter::ImportType type )
{
    DocumentImporter *importer = 0;
    if( type == DocumentImporter::IT_FILE )
    {
        static QString previousFolder = QDir( QDir::currentPath() ).dirName();
        QFileDialog openDialog( this );
        openDialog.setDirectory( previousFolder );
        openDialog.setAcceptMode( QFileDialog::AcceptOpen );
        openDialog.setWindowTitle( "Import document" );
        openDialog.setNameFilter( "Supported files (*.png *.svg)" );

        if( openDialog.exec() == QFileDialog::Accepted )
        {
            QString fileName = openDialog.selectedFiles().at( 0 );
            importer = new DocumentImporter( fileName );
        }
        else
        {
            return false;
        }
    }
    else
        importer = new DocumentImporter();

    if( ! importer->parse() )
    {
        QMessageBox mb( QMessageBox::Critical, "Failed to import", "The specified file has not been produced by us", QMessageBox::Ok, this );
        mb.exec();

        return false;
    }

    // Check if we already have the document open (based on it's uuid)
    QUuid uuid( importer->source().Uuid );
    DocumentEditor *editor = getDocumentTabForUuid( uuid );
    if( editor == 0 )
    {
        switch( type )
        {
        case DocumentImporter::IT_FILE:
            editor = addDocumentTab( importer->type(), QFileInfo( importer->fileName() ).fileName() );
            break;
        case DocumentImporter::IT_CLIPBOARD:
            editor = addDocumentTab( importer->type(), importer->fileName() );
            break;
        }
    }
    else
        switchToDocument( editor->uuid() );
    editor->setDocumentFromSource( importer->source() );

    debug() << "Imported-Template: " << importer->source().Template;
    debug() << "Imported-Source  : " << importer->source().Source;
    debug() << "Imported-Type    : " << importer->source().Type;
    debug() << "Imported-UUID    : " << importer->source().Uuid;

    // Compile the document
    buttonCompilePressed( false );

    return true;
}

// PRIVATE SLOTS
void MainWindow::buttonCompilePressed( bool checked )
{
    debug() << "Compile button";

    // Connect the signals to receive compilation step changes
    QObject::connect( m_ActiveDocument, SIGNAL(compilationStep(QString,int)),this,SLOT(compilationStep(QString,int)));

    // Disable the User Interface
    setEnabled( false );

    // If compilation took more than 500 msec's show the progress indicator dialog
    QTimer compilationTimeout;
    QObject::connect( &compilationTimeout, SIGNAL(timeout()), this, SLOT(showProgressIndicator()));
    compilationTimeout.start( 500 );

    if( ! m_ActiveDocument->compile() )
    {
        m_UserInterface->buttonErrorLog->setEnabled( true );
        m_UserInterface->buttonCopyClipboard->setEnabled( false );
    } else {
        m_UserInterface->buttonErrorLog->setEnabled( false );
        m_UserInterface->buttonCopyClipboard->setEnabled( true );
    }

    // Disconnect the signal again
    QObject::disconnect( m_ActiveDocument, SIGNAL(compilationStep(QString,int)), this, SLOT(compilationStep(QString,int)));

    // Enable the user interface
    setEnabled( true );
    m_ProgressIndicator->hide();

    // Set the Editor widget focused
    m_ActiveDocument->focusInputTextbox();
}

void MainWindow::buttonErrorLogPressed( bool checked )
{
    debug() << "Error Log button";
    m_ErrorLog->setMessage( m_ActiveDocument->compilerLog() );
    m_ErrorLog->show();
}

void MainWindow::buttonCopyClipboardPressed( bool checked )
{
    debug() << "Copy to clipboard button";
    m_ActiveDocument->copyImageToClipboard();
}

// The active document has changed it's status, so we need to (eventually)
// change the button states.
void MainWindow::activeDocumentStatusChanged()
{
    debug() << QString( "MainWindow::activeDocumentStatusChanged: Document [%1] changed it's status" ).arg( m_ActiveDocument->name() );
    checkActiveDocumentStatus();
}

void MainWindow::tabCloseRequested( int index )
{
    debug() << "Close requested";

    DocumentEditor *documentToClose = ( DocumentEditor * ) m_UserInterface->tabWidget->widget( index );
    debug() << "    -> Tab Name: " << documentToClose->name();

    // Remove the Tab - if it's the last tab we close, create a new one which is empty to replace
    // this last tab.
    QTabWidget *tw = m_UserInterface->tabWidget;
    tw->removeTab( index );
    delete documentToClose;

    if( tw->count() == 0 )
    {
        debug() << "Creating new tab because last tab was closed by user";
        addDocumentTab( DT_LATEX, generateEmptyTabName() );
    }
}

void MainWindow::tabWidgetIndexChanged( int index )
{
    debug() << "Tab index changed to: " << index;
    if( index < 0 )
    {
        debug() << "   -> negative, no tab open anymore";
        return;
    }

    m_ActiveDocument = ( DocumentEditor * ) m_UserInterface->tabWidget->currentWidget();
    debug() << "Active Template for this editor: " << m_ActiveDocument->documentLatexTemplate().name();

    // Connect to the active document's change status signal
    QObject::connect( m_ActiveDocument, SIGNAL(documentStatusChanged()), this, SLOT(activeDocumentStatusChanged()));

    // Activate/Deactivate Copy/Error Log buttons according
    // to document status
    checkActiveDocumentStatus();

    // Set the Template selector to the current selected one
    setTemplateSelection();
}

void MainWindow::menuFileQuitPressed( bool checked )
{
    QApplication::quit();
}

void MainWindow::menuFileExportSvgPressed( bool checked )
{
    debug() << "MainWindow: Export as SVG";
    exportCurrentDocument( IT_SVG );
}

void MainWindow::menuFileExportPngPressed( bool checked )
{
    debug() << "MainWindow: Export as PNG";
    exportCurrentDocument( IT_PNG );
}

void MainWindow::menuFileImportPressed( bool checked )
{
    debug() << "MainWindow: Import document from file ";
    importDocument( DocumentImporter::IT_FILE );
}

void MainWindow::menuEditPastePressed( bool checked )
{
    // Pasting document from clipboard if supported
    debug() << "MainWindow: Import document from clipboard";
    importDocument( DocumentImporter::IT_CLIPBOARD );
}

void MainWindow::menuEditOptionsPressed( bool checked )
{
    SettingsDialog dialog( this );
    dialog.exec();

    // Reload templates in case they changed
    setupTemplateList();
    setTemplateSelection();

    if( m_Settings->valid() )
        setStatusMessage( false );
}

void MainWindow::menuViewZoomInPressed( bool checked )
{
    debug() << "Preview zoom in";

    qreal currentScale = m_ActiveDocument->zoomIn();
    debug() << "   new scale: " << currentScale;
}

void MainWindow::menuViewZoomOutPressed( bool checked )
{
    debug() << "Preview zoom out";

    qreal currentScale = m_ActiveDocument->zoomOut();
    debug() << "   new scale: " << currentScale;
}

void MainWindow::menuViewZoomOriginalPressed( bool checked )
{
    debug() << "Preview zoom normal";

    qreal currentScale = m_ActiveDocument->zoomNormal();
    debug() << "   new scale: " << currentScale;
}

void MainWindow::menuAddLatexDocumentPressed()
{
    debug() << "MainWindow: Adding LaTeX Document Tab";
    addDocumentTab( DT_LATEX, generateEmptyTabName() );
}

void MainWindow::menuAddSketchDocumentPressed()
{
    debug() << "MainWindow: Adding Sketch Document Tab";
    addDocumentTab( DT_SKETCH, generateEmptyTabName() );
}

void MainWindow::menuHelpAboutPressed( bool checked )
{
    debug() << "MainWindow: Showing About dialog";

    AboutDialog aboutDialog( this );
    aboutDialog.exec();
}

void MainWindow::toolbarCopyModeSelectorIndexChanged( const QString &copyMode )
{
    ClipboardCopyType newMode;
    if( copyMode == "SVG" )
        newMode = CCT_SVG;
    else if( copyMode == "PNG" )
        newMode = CCT_PNG;
    else if( copyMode == "Code" )
        newMode = CCT_CODE;
    else
        newMode = CCT_PNG;

    m_ActiveDocument->setClipboardCopyMode( newMode );
}

void MainWindow::toolbarTemplateSelectorIndexChanged(const QString &templateName)
{
    Template t = m_Settings->getLatexTemplate( templateName );
    debug() << t.code();

    m_ActiveDocument->setDocumentLatexTemplate( t );
}

void MainWindow::setTemplateSelection()
{
    Template t = m_ActiveDocument->documentLatexTemplate();

    // Check if we have the template and set it
    for( int i = 0; i < m_TemplateSelectorComboBox->count(); i ++ )
    {
        if( m_TemplateSelectorComboBox->itemText( i ).compare( t.name() ) == 0 )
        {
            m_TemplateSelectorComboBox->setCurrentIndex( i );
            break;
        }
    }
}

// Check the currently active Document Editor for his status
// and set the buttons correctly enabled/disabled
void MainWindow::checkActiveDocumentStatus()
{
    if( m_ActiveDocument->canCompile() )
        m_UserInterface->buttonCompile->setEnabled( true );
    else
        m_UserInterface->buttonCompile->setEnabled( false );

    if( m_ActiveDocument->hasError() )
        m_UserInterface->buttonErrorLog->setEnabled( true );
    else
        m_UserInterface->buttonErrorLog->setEnabled( false );

    if( m_ActiveDocument->canCopy() )
        m_UserInterface->buttonCopyClipboard->setEnabled( true );
    else
        m_UserInterface->buttonCopyClipboard->setEnabled( false );

    // Set Copy Type to match the DocumentEditor
    ClipboardCopyType copyMode = m_ActiveDocument->clipboardCopyMode();
    m_CopySelectorComboBox->setCurrentIndex( copyMode );

    // Disable/Enable UI elements according to Document Type
    switch( m_ActiveDocument->documentType() )
    {
    case DT_LATEX:
        m_TemplateSelectorComboBox->setEnabled( true );
        break;

    case DT_SKETCH:
        m_TemplateSelectorComboBox->setEnabled( false );
        break;

    default:
        break;
    }

    // Enable/Disable all export functionality according to document status
    if( ! m_ActiveDocument->hasError() && m_ActiveDocument->canCopy() )
        m_UserInterface->menu_Export->setEnabled( true );
    else
        m_UserInterface->menu_Export->setEnabled( false );

}

void MainWindow::setStatusMessage( bool enabled, const QString &message, const QColor &color )
{
    // Set color of Status label
    m_StatusLabel->setStyleSheet( QString( "color: rgb(%1, %2, %3);" ).arg( color.red() ).arg( color.green() ).arg( color.blue() ));

    if( ! enabled )
    {
        m_StatusLabel->setText("");
        return;
    }

    m_StatusLabel->setText( message );
}

void MainWindow::compilationStep(const QString &message, int step)
{
    debug() << "MainWindow::compilationStep";
    m_ProgressIndicator->setStatus( message, step );
}

void MainWindow::showProgressIndicator()
{
    // Show the progress indicator if it's not visible already
    if( ! m_ProgressIndicator->isVisible() )
    {
        m_ProgressIndicator->show();
    }
}

// PROTECTED
void MainWindow::closeEvent( QCloseEvent *event )
{
    // Save the window geometry and state to the persistent configuration
    m_Settings->setWindowGeometry( saveGeometry() );
    m_Settings->setWindowState( saveState() );
}

void MainWindow::resizeEvent( QResizeEvent *event )
{
    QMainWindow::resizeEvent( event );

    // Recenter the progress indicator to have it's new
    // centered position above everything else
    m_ProgressIndicator->centerOnParent();
}

void MainWindow::showEvent( QShowEvent *event )
{
    QMainWindow::showEvent( event );
    m_ActiveDocument->focusInputTextbox();

    // Restore window geometry and state
    restoreGeometry( m_Settings->windowGeometry() );
    restoreState( m_Settings->windowState() );
}

// PUBLIC
MainWindow::MainWindow() : QMainWindow( 0 ), m_TabCounter(0)
{
    m_Settings = SettingsProvider::instance();

    setupUserInterface();
    addDocumentTab( DT_LATEX, generateEmptyTabName() );
    addAdderTab();

    m_ProgressIndicator = new ProgressIndicator( this );
    m_ProgressIndicator->hide();

    m_ErrorLog = new ErrorLog();
    m_ErrorLog->setWindowModality( Qt::ApplicationModal );

    // Are the settings valid?
    if( ! m_Settings->valid() )
    {
        setStatusMessage( true, "Configuration invalid!", QColor( 255, 0, 0));
    }

    // FOR TESTING
    //m_MathSyms = new MathSyms();
    //m_MathSyms->show();
}

MainWindow::~MainWindow()
{
    //delete m_MathSyms;
    delete m_UserInterface;
}
