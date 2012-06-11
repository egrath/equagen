#include "DocumentEditor.h"

void DocumentEditor::setupUserInterface()
{
    m_UserInterface = new Ui_DocumentEditor();
    m_UserInterface->setupUi( this );

    // Connect editor
    QObject::connect( m_UserInterface->textEditTex, SIGNAL(textChanged()), this, SLOT(textEditorTextChanged()));

    // Connect mouse wheel event of Preview scroll area
    QObject::connect( m_UserInterface->scrollArea, SIGNAL(mouseWheelEvent(QWheelEvent*)), this, SLOT( previewScrollerMouseWheelEvent(QWheelEvent*)));

    // Splitter drag handle
    QObject::connect( m_UserInterface->splitterPane, SIGNAL(splitterMoved(int,int)), this, SLOT(splitterPaneHandleMoved(int,int)));
}

// Makes the splitter pane's children equally sized
void DocumentEditor::setupSplitterPane()
{
    QList<int> paneSizes;
    QSplitter *splitter = m_UserInterface->splitterPane;

    if( m_TextEditorWidth == -1 )
    {
        // Make the Text Editor 30 chars width per default
        QFontMetrics fontMetric( m_UserInterface->textEditTex->font() );
        int charWidth = fontMetric.width( 'A' );

        qDebug() << "DocumentEditor: Setting Text Editor width to " << charWidth * 30 << " because one char is " << charWidth << " pixels wide";
        m_TextEditorWidth = charWidth * 30;
    }

    QSize splitterSize = splitter->size();
    int left = m_TextEditorWidth;
    int right = splitterSize.width() - left;

    paneSizes.append( left );
    paneSizes.append( right );

    splitter->setSizes( paneSizes );
}

// Special helper method to return a image with a 1 pixel border
// and white background - needed for openoffice clipboard copy (because it looks ugly otherwise)
QImage DocumentEditor::preparePngImageForClipboard() const
{
    QImage sourceImage = QImage::fromData( *( m_Document->pngImage().rawContent() ));
    QImage destinationImage( sourceImage.size().width() + 4, sourceImage.size().height() + 4, QImage::Format_ARGB32 );

    QPainter destinationPainter( &destinationImage );
    destinationPainter.fillRect( 0, 0, destinationImage.width(), destinationImage.height(), Qt::white );
    destinationPainter.drawImage( 2, 2, sourceImage );

    return destinationImage;
}

void DocumentEditor::textEditorTextChanged()
{
    QString text = m_UserInterface->textEditTex->document()->toPlainText();

    // Check if we are (theoretically) able to compile...
    if( text.length() > 0 )
        m_CanCompile = true;
    else
        m_CanCompile = false;

    // Inform everyone interested that we have changed our status....
    emit documentStatusChanged();

    // Set the Text to the Document
    m_Document->setPlainContent( text );
}

// Event handler for Preview scroll area mouse wheel event
void DocumentEditor::previewScrollerMouseWheelEvent( QWheelEvent *event )
{
    if( event->delta() > 0 )
        zoomIn();
    else
        zoomOut();
}

// Event handler for SettingsProvider, called when the settings have changed
void DocumentEditor::configurationSettingsChanged()
{
    qDebug() << "DocumentEditor: configuration settings changed";
}

// Event handler for document compilation status changed
void DocumentEditor::compilationStepHandler(const QString &message, int step)
{
    emit compilationStep( message, step );
}

// Splitter pane handle moved
void DocumentEditor::splitterPaneHandleMoved(int pos, int index)
{
    qDebug() << "Splitter pane moved to pos: " << pos;
    m_TextEditorWidth = pos;
}

// PROTECTED
void DocumentEditor::showEvent( QShowEvent *event )
{
    qDebug() << "DocumentEditor::showEvent";
    QWidget::showEvent( event );

    //setupSplitterPane();
}

void DocumentEditor::resizeEvent( QResizeEvent *event )
{
    qDebug() << "DocumentEditor::resizeEvent to " << event->size();
    QWidget::resizeEvent( event );

    setupSplitterPane();
}

// PUBLIC
void DocumentEditor::copyImageToClipboard() const
{
    if( ! m_Document->documentValid() ) // Current document is invalid, return
        return;

    QClipboard *clip = QApplication::clipboard();
    QMimeData *mimeData = 0;
    QImage clipboardImage;

    clip->clear();

    switch( m_ClipboardCopyType )
    {
    case CCT_SVG:
        qDebug() << "Copying SVG to clipboard ...";

        mimeData = new QMimeData();
        mimeData->setData( "image/svg+xml", *( m_Document->svgImage().rawContent() ));
        clip->setMimeData( mimeData );
        break;

    case CCT_PNG:
        qDebug() << "Copying PNG to clipboard ...";

        clipboardImage = preparePngImageForClipboard();
        clip->setImage( clipboardImage );
        break;

    default:
        break;
    }
}

DocumentEditor::DocumentEditor( DocumentType type, const QString &name, const QString &initialContent, QWidget *parent ) : QWidget( parent ), m_TextEditorWidth( -1 )
{
    setupUserInterface();

    // Create the underlaying document
    try
    {
        m_Document = DocumentFactory::instance()->createDocument( type );
        QObject::connect( m_Document, SIGNAL(compilationStep(QString,int)), this, SLOT(compilationStepHandler(QString,int)));
    }
    catch( QString *msg )
    {
        qDebug() << "Exception: " << *msg;
    }

    m_Document->setName( name );
    m_Document->setPlainContent( initialContent );

    m_Renderer = m_UserInterface->renderer;
    m_PreviewScrollArea = m_UserInterface->scrollArea;

    // Status indicators
    m_IsModified = false;
    m_CanCompile = false;
    m_HasError = false;

    // Get settings provider
    m_Settings = SettingsProvider::instance();

    // We want to get informed if the user has changed global settings
    QObject::connect( m_Settings, SIGNAL(configurationSettingsChanged()), this, SLOT(configurationSettingsChanged()));

    // Set default clipboard copy type to SVG
    setClipboardCopyMode( CCT_SVG );
}

DocumentEditor::~DocumentEditor()
{
    delete m_Document;
}

bool DocumentEditor::compile()
{
    // Just a safety check, this should always return true if we
    // came here
    if( ! canCompile() )
        return false;

    // Start a new thread which does the actual compilation
    DocumentCompiler compiler( m_Document );
    compiler.start();

    // Wait until the thread has finished
    while( compiler.isRunning() )
        QApplication::processEvents();

    // Check for errors
    if( compiler.finishedWithError() )
    {
        qDebug() << "Compiler error message: " << compiler.compilerErrorMessage();

        QMessageBox errorBox( QMessageBox::Critical, "Compilation failed", "Compilation failed, check log",
                              QMessageBox::Ok );
        errorBox.exec();

        // We have a error in the document, set the flag
        m_HasError = true;

        // Inform everyone interested that we have changed our status ....
        emit documentStatusChanged();

        return false;
    }

    m_Renderer->setImage( m_Document->svgImage() );
    m_Renderer->repaint();

    // Everything went as expected
    m_HasError = false;

    // Inform everyone interested that we have changed our status....
    emit documentStatusChanged();

    return true;
}

// Get the last error message from compile time
const QString & DocumentEditor::compilerLog() const
{
    return m_Document->lastCompileError();
}

// Was the last compile successful?
bool DocumentEditor::lastCompileSuccessfull() const
{
    return m_Document->documentValid();
}

// Is the document modified?
bool DocumentEditor::isModified() const
{
    return m_IsModified;
}

// Can we compile (theoretically, text len > 0)
bool DocumentEditor::canCompile() const
{
    return m_CanCompile;
}

// Do we have a finished image to copy to the clipboard
bool DocumentEditor::canCopy() const
{
    return m_Document->documentValid();
}

// Has the document an error? (Last compile failed)
bool DocumentEditor::hasError() const
{
    return m_HasError;
}

void DocumentEditor::setName( const QString &name )
{
    m_Document->setName( name );
}

const QString & DocumentEditor::name() const
{
    return m_Document->name();
}

const QUuid & DocumentEditor::uuid() const
{
    return m_Document->uuid();
}

// Set the Clipboard Copy Type
void DocumentEditor::setClipboardCopyMode( ClipboardCopyType type )
{
    m_ClipboardCopyType = type;

    qDebug() << "Document Editor: setting new copy mode to: " << type;
}

const ClipboardCopyType & DocumentEditor::clipboardCopyMode() const
{
    return m_ClipboardCopyType;
}

bool DocumentEditor::setDocumentFromSource( const OriginalSource & source )
{
    // Set source text in editor
    m_UserInterface->textEditTex->clear();
    m_UserInterface->textEditTex->textCursor().insertText( source.Source );

    // Set source (and template) in document
    m_Document->setPlainContent( source.Source );
    if( m_Document->documentType() == DT_LATEX )
    {
        (( DocumentLatex * ) m_Document )->setTexTemplate( source.Template );
    }

    // Set UUID
    m_Document->setUuid( QUuid( source.Uuid ));

    return true;
}

bool DocumentEditor::exportDocumentToFile( ImageType type, const QString &fileName )
{
    QFile exportFile( fileName );
    exportFile.open( QFile::WriteOnly );

    if( type == IT_SVG )
    {
        // Save as SVG
        exportFile.write( *( m_Document->svgImage().rawContent() ));
        exportFile.close();
        return true;
    }
    else if( type == IT_PNG )
    {
        // Save as PNG
        exportFile.write( *( m_Document->pngImage().rawContent() ));
        exportFile.close();
        return true;
    }

    // If for some reason we haven't written the export, remove the empty file
    exportFile.close();
    QFile::remove( fileName );

    return false;
}

const DocumentType & DocumentEditor::documentType() const
{
    return m_Document->documentType();
}

void DocumentEditor::focusInputTextbox()
{
    m_UserInterface->textEditTex->setFocus( Qt::OtherFocusReason );
}

qreal DocumentEditor::zoomIn()
{
    qreal scale = m_Renderer->scale();
    scale *= 1.1;

    m_Renderer->setScale( scale );
    return scale;
}

qreal DocumentEditor::zoomOut()
{
    qreal scale = m_Renderer->scale();
    if( scale >= 0.2 )
        scale /= 1.1;

    m_Renderer->setScale( scale );
    return scale;
}

qreal DocumentEditor::zoomNormal()
{
    qreal defaultPreviewScale = m_Settings->previewScale();
    m_Renderer->setScale( defaultPreviewScale );

    return defaultPreviewScale;
}
