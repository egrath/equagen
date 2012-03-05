#include "DocumentEditor.h"

void DocumentEditor::setupUserInterface()
{
    m_UserInterface = new Ui_DocumentEditor();
    m_UserInterface->setupUi( this );

    // Connect editor
    QObject::connect( m_UserInterface->textEditTex, SIGNAL(textChanged()), this, SLOT(textEditorTextChanged()));

    // Connect mouse wheel event of Preview scroll area
    QObject::connect( m_UserInterface->scrollArea, SIGNAL(mouseWheelEvent(QWheelEvent*)), this, SLOT( previewScrollerMouseWheelEvent(QWheelEvent*)));
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

DocumentEditor::DocumentEditor( DocumentType type, const QString &name, const QString &initialContent, QWidget *parent ) : QWidget( parent )
{
    setupUserInterface();

    // Create the underlaying document
    m_Document = DocumentFactory::instance()->createDocument( type );
    m_Document->setName( name );
    m_Document->setPlainContent( initialContent );

    m_Renderer = m_UserInterface->renderer;
    m_PreviewScrollArea = m_UserInterface->scrollArea;

    // Status indicators
    m_IsModified = false;
    m_CanCompile = false;
    m_HasError = false;

    // Get settings provider
    m_Settings = SettingsProvider::getInstance();

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

    try
    {
        m_Document->compile();
    }
    catch( QString *exception )
    {
        qDebug() << "Got exception: " << *exception;

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

const DocumentType & DocumentEditor::documentType() const
{
    return m_Document->documentType();
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
