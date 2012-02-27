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

    // Connect Edit->Options dialog
    QObject::connect( m_UserInterface->actionEditOptions, SIGNAL( triggered( bool )), this, SLOT( menuEditOptionsPressed(bool)));

    // Connect File->Quit
    QObject::connect( m_UserInterface->actionFileQuit, SIGNAL( triggered( bool )), this, SLOT( menuFileQuitPressed(bool)));

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
    QComboBox *templateSelectorComboBox = new QComboBox();
    templateSelectorComboBox->addItem( "Built-in Template" );
    templateSelectorComboBox->setCurrentIndex( 0 );
    m_UserInterface->toolBar->addSeparator();
    m_UserInterface->toolBar->addWidget( templateSelectorLabel );
    m_UserInterface->toolBar->addWidget( templateSelectorComboBox );

    // Add PNG/SVG Copy Mode selector
    QLabel *copySelectorLabel = new QLabel( "Clipboard type" );
    QComboBox *copySelectorComboBox = new QComboBox();
    copySelectorComboBox->addItem( "PNG" );
    copySelectorComboBox->addItem( "SVG" );
    copySelectorComboBox->setCurrentIndex( 1 );
    m_UserInterface->toolBar->addSeparator();
    m_UserInterface->toolBar->addWidget( copySelectorLabel );
    m_UserInterface->toolBar->addWidget( copySelectorComboBox );
}

// Insert a new Document Editor Tab
void MainWindow::addDocumentTab( const QString &name )
{
    qDebug() << "MainWindow::addDocumentTab";

    QTabWidget *tw = m_UserInterface->tabWidget;

    // Build Tab content
    DocumentEditor *editor = new DocumentEditor( name );
    m_Documents.append( editor );

    // Append to Tab Widget
    int tabIndex = m_Documents.count() -1;
    qDebug() << QString( "    Adding new Tab with Name %1 and ID %2" ).arg( name ).arg( tabIndex );
    tw->insertTab( tabIndex, editor, name );

    // Switch to this Tab
    tw->setCurrentIndex( tabIndex );
}

void MainWindow::addAdderTab()
{
    QTabWidget *tw = m_UserInterface->tabWidget;
    QLabel *label = new QLabel( "You are not supposed to see me!" );

    tw->addTab( label, QIcon( ":/icons/list-add.svg" ), "" );
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

// The active document has changed it's status, so we need to (eventually)
// change the button states.
void MainWindow::activeDocumentStatusChanged()
{
    qDebug() << QString( "MainWindow::activeDocumentStatusChanged: Document [%1] changed it's status" ).arg( m_ActiveDocument->name() );
    checkActiveDocumentStatus();
}

void MainWindow::tabWidgetIndexChanged( int index )
{
    qDebug() << "Tab index changed to: " << index;

    // Check if the user has changed to the Adder tab
    if( index >= m_Documents.count() )
    {
        qDebug() << "MainWindow::tabWidgetIndexChanged - adding a new tab!";
        addDocumentTab( QString( "Untitled-%1" ).arg( m_Documents.count() +1 ));
        return;
    }

    m_ActiveDocument = m_Documents.at( index );

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
}

void MainWindow::menuViewZoomOutPressed( bool checked )
{
    qDebug() << "Preview zoom out";
}

void MainWindow::menuViewZoomOriginalPressed( bool checked )
{
    qDebug() << "Preview zoom normal";
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

// PUBLIC
MainWindow::MainWindow() : QMainWindow( 0 )
{
    setupUserInterface();       
    addDocumentTab( QString( "Untitled-%1" ).arg( m_Documents.count() +1 ));
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
