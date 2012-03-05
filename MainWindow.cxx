#include "MainWindow.h"

void MainWindow::setupUserInterface()
{
    m_UserInterface = new Ui_MainWindow();
    m_UserInterface->setupUi( this );

    // Create Label for Status messages
    m_StatusLabel = new QLabel( "", m_UserInterface->statusbar );
    m_UserInterface->statusbar->addWidget( m_StatusLabel );

    // Connect signals
    QObject::connect( m_UserInterface->actionButtonCompile, SIGNAL(triggered(bool)), this, SLOT(buttonCompilePressed(bool)));
    QObject::connect( m_UserInterface->actionButtonErrorLog,SIGNAL(triggered(bool)),this,SLOT(buttonErrorLogPressed(bool)));
    QObject::connect( m_UserInterface->actionButtonCopyClipboard,SIGNAL(triggered(bool)),this,SLOT(buttonCopyClipboardPressed(bool)));
    QObject::connect( m_UserInterface->tabWidget, SIGNAL(currentChanged(int)),this,SLOT(tabWidgetIndexChanged(int)));
    QObject::connect( m_UserInterface->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(tabCloseRequested(int)));

    // Connect Edit->Options dialog
    QObject::connect( m_UserInterface->actionEditOptions, SIGNAL( triggered( bool )), this, SLOT( menuEditOptionsPressed(bool)));

    // Connect File Menu
    QObject::connect( m_UserInterface->actionFileQuit, SIGNAL( triggered( bool )), this, SLOT( menuFileQuitPressed(bool)));
    QObject::connect( m_UserInterface->actionFileExportPng, SIGNAL(triggered(bool)), this, SLOT(menuFileExportPngPressed(bool)));
    QObject::connect( m_UserInterface->actionFileExportSvg, SIGNAL(triggered(bool)), this, SLOT(menuFileExportSvgPressed(bool)));

    // Connect View Items
    QObject::connect( m_UserInterface->actionViewZoomIn, SIGNAL( triggered( bool )), this, SLOT( menuViewZoomInPressed(bool)));
    QObject::connect( m_UserInterface->actionViewZoomOut, SIGNAL(triggered(bool)), this, SLOT(menuViewZoomOutPressed(bool)));
    QObject::connect( m_UserInterface->actionViewNormalSize, SIGNAL( triggered(bool)),this,SLOT(menuViewZoomOriginalPressed(bool)));

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
    m_TemplateSelectorComboBox->addItem( "Built-in Template" );
    m_TemplateSelectorComboBox->setCurrentIndex( 0 );
    m_UserInterface->toolBar->addSeparator();
    m_UserInterface->toolBar->addWidget( templateSelectorLabel );
    m_UserInterface->toolBar->addWidget( m_TemplateSelectorComboBox );

    // Add PNG/SVG Copy Mode selector
    QLabel *copySelectorLabel = new QLabel( "Clipboard type" );
    m_CopySelectorComboBox = new QComboBox();
    m_CopySelectorComboBox->addItem( "PNG" );
    m_CopySelectorComboBox->addItem( "SVG" );
    m_CopySelectorComboBox->setCurrentIndex( 1 );
    m_UserInterface->toolBar->addSeparator();
    m_UserInterface->toolBar->addWidget( copySelectorLabel );
    m_UserInterface->toolBar->addWidget( m_CopySelectorComboBox );

    // Connect
    QObject::connect( m_CopySelectorComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(toolbarCopyModeSelectorIndexChanged(QString)));
}

// Insert a new Document Editor Tab
void MainWindow::addDocumentTab( const QString &name )
{
    qDebug() << "MainWindow::addDocumentTab";

    QTabWidget *tw = m_UserInterface->tabWidget;

    // Build Tab content
    DocumentEditor *editor = new DocumentEditor( DT_LATEX, name );

    // Append to Tab Widget
    int tabIndex = tw->count();
    qDebug() << QString( "    Adding new Tab with Name %1 and ID %2" ).arg( name ).arg( tabIndex );
    tw->insertTab( tabIndex, editor, name );

    // Switch to this Tab
    tw->setCurrentIndex( tabIndex );

    // Tell Document Editor's input widget to take the focus
    editor->setFocus( Qt::TabFocusReason );
}

void MainWindow::addAdderTab()
{
    QTabWidget *tw = m_UserInterface->tabWidget;
    QPushButton *addTabButton = new QPushButton( QIcon( ":/icons/list-add.svg" ), "" );

    QObject::connect( addTabButton, SIGNAL( clicked() ), this, SLOT( buttonAddDocumentEditorTabButtonPressed()) );

    tw->setCornerWidget( addTabButton, Qt::TopLeftCorner );
}

QString MainWindow::generateEmptyTabName()
{
    return QString( "Untitled-%1" ).arg( m_TabCounter++ );
}

void MainWindow::buttonCompilePressed( bool checked )
{
    qDebug() << "Compile button";
    if( ! m_ActiveDocument->compile() )
    {
        m_UserInterface->buttonErrorLog->setEnabled( true );
        m_UserInterface->buttonCopyClipboard->setEnabled( false );
    } else {
        m_UserInterface->buttonErrorLog->setEnabled( false );
        m_UserInterface->buttonCopyClipboard->setEnabled( true );
    }
}

void MainWindow::buttonErrorLogPressed( bool checked )
{
    qDebug() << "Error Log button";
    m_ErrorLog->setMessage( m_ActiveDocument->compilerLog() );
    m_ErrorLog->show();
}

void MainWindow::buttonCopyClipboardPressed( bool checked )
{
    qDebug() << "Copy to clipboard button";
    m_ActiveDocument->copyImageToClipboard();
}

void MainWindow::buttonAddDocumentEditorTabButtonPressed()
{
    qDebug() << "Add Document Editor Tab Button pressed";

    addDocumentTab( generateEmptyTabName() );
}

// The active document has changed it's status, so we need to (eventually)
// change the button states.
void MainWindow::activeDocumentStatusChanged()
{
    qDebug() << QString( "MainWindow::activeDocumentStatusChanged: Document [%1] changed it's status" ).arg( m_ActiveDocument->name() );
    checkActiveDocumentStatus();
}

void MainWindow::tabCloseRequested( int index )
{
    qDebug() << "Close requested";

    DocumentEditor *documentToClose = ( DocumentEditor * ) m_UserInterface->tabWidget->widget( index );
    qDebug() << "    -> Tab Name: " << documentToClose->name();

    // Remove the Tab - if it's the last tab we close, create a new one which is empty to replace
    // this last tab.
    QTabWidget *tw = m_UserInterface->tabWidget;
    tw->removeTab( index );
    delete documentToClose;

    if( tw->count() == 0 )
    {
        qDebug() << "Creating new tab because last tab was closed by user";
        addDocumentTab( generateEmptyTabName() );
    }
}

void MainWindow::tabWidgetIndexChanged( int index )
{
    qDebug() << "Tab index changed to: " << index;
    if( index < 0 )
    {
        qDebug() << "   -> negative, no tab open anymore";
        return;
    }

    m_ActiveDocument = ( DocumentEditor * ) m_UserInterface->tabWidget->currentWidget();

    // Connect to the active document's change status signal
    QObject::connect( m_ActiveDocument, SIGNAL(documentStatusChanged()), this, SLOT(activeDocumentStatusChanged()));

    // Activate/Deactivate Copy/Error Log buttons according
    // to document status
    checkActiveDocumentStatus();
}

void MainWindow::menuFileQuitPressed( bool checked )
{
    QApplication::quit();
}

void MainWindow::menuFileExportSvgPressed( bool checked )
{
    qDebug() << "MainWindow: Export as SVG";

    QString fileName = showFileDialog( QFileDialog::AcceptSave );
}

void MainWindow::menuFileExportPngPressed( bool checked )
{
    qDebug() << "MainWindow: Export as PNG";
}

void MainWindow::menuEditOptionsPressed( bool checked )
{
    SettingsDialog dialog( this );
    dialog.exec();

    if( m_Settings->valid() )
        setStatusMessage( false );
}

void MainWindow::menuViewZoomInPressed( bool checked )
{
    qDebug() << "Preview zoom in";

    qreal currentScale = m_ActiveDocument->zoomIn();
    qDebug() << "   new scale: " << currentScale;
}

void MainWindow::menuViewZoomOutPressed( bool checked )
{
    qDebug() << "Preview zoom out";

    qreal currentScale = m_ActiveDocument->zoomOut();
    qDebug() << "   new scale: " << currentScale;
}

void MainWindow::menuViewZoomOriginalPressed( bool checked )
{
    qDebug() << "Preview zoom normal";

    qreal currentScale = m_ActiveDocument->zoomNormal();
    qDebug() << "   new scale: " << currentScale;
}

void MainWindow::toolbarCopyModeSelectorIndexChanged( const QString &copyMode )
{
    ClipboardCopyType newMode;
    if( copyMode == "SVG" )
        newMode = CCT_SVG;
    else if( copyMode == "PNG" )
        newMode = CCT_PNG;

    m_ActiveDocument->setClipboardCopyMode( newMode );
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

QString MainWindow::showFileDialog( QFileDialog::AcceptMode acceptMode )
{
    static QString directory = QDir::current().dirName();
    QString fileName = "";

    QFileDialog fileDialog;
    fileDialog.setAcceptMode( acceptMode );
    fileDialog.setAcceptDrops( true  );
    fileDialog.setDirectory( directory );

    if( fileDialog.exec() )
    {
        fileName = fileDialog.selectedFiles().at( 0 );
        directory = QDir( fileName ).dirName();

        qDebug() << fileName;
        qDebug() << directory;
    }

    return fileName;
}

// PUBLIC
MainWindow::MainWindow() : QMainWindow( 0 ), m_TabCounter(0)
{
    setupUserInterface();       
    addDocumentTab( generateEmptyTabName() );
    addAdderTab();

    m_ErrorLog = new ErrorLog();
    m_ErrorLog->setWindowModality( Qt::ApplicationModal );

    m_Settings = SettingsProvider::getInstance();
    if( ! m_Settings->valid() )
    {
        setStatusMessage( true, "Configuration invalid!", QColor( 255, 0, 0));
    }
}

MainWindow::~MainWindow()
{
    delete m_UserInterface;
}
