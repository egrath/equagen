#ifndef EQUATIONEDITOR_H
#define EQUATIONEDITOR_H

#include <QtGui>

#include "DocumentEditor.h"
#include "DocumentImporter.h"
#include "ErrorLog.h"
#include "SettingsDialog.h"
#include "ProgressIndicator.h"
#include "AboutDialog.h"

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    // UI stuff
    Ui_MainWindow *m_UserInterface;
    QLabel *m_StatusLabel;
    QComboBox *m_CopySelectorComboBox;
    QComboBox *m_TemplateSelectorComboBox;

    ProgressIndicator *m_ProgressIndicator;

    // Document stuff
    DocumentEditor *m_ActiveDocument;
    ErrorLog *m_ErrorLog;

    SettingsProvider *m_Settings;

    int m_TabCounter;

    void setupUserInterface();
    void setupToolbar();
    void switchToDocument( const QUuid &uuid );
    DocumentEditor * addDocumentTab( DocumentType type, const QString &name );
    DocumentEditor * getDocumentTabForUuid( const QUuid &uuid );
    void addAdderTab();

    QString generateEmptyTabName();

    void checkActiveDocumentStatus();
    void setStatusMessage( bool enabled, const QString &message = "", const QColor & color = QColor( 0, 0, 0 ));

    bool exportCurrentDocument( ImageType type );
    bool importDocument( DocumentImporter::ImportType type );

private slots:
    void buttonCompilePressed( bool checked );
    void buttonErrorLogPressed( bool checked );
    void buttonCopyClipboardPressed( bool checked );

    void tabWidgetIndexChanged( int index );
    void tabCloseRequested( int index );
    void activeDocumentStatusChanged();

    void menuFileQuitPressed( bool checked );
    void menuFileExportSvgPressed( bool checked );
    void menuFileExportPngPressed( bool checked );
    void menuFileImportPressed( bool checked );
    void menuEditPastePressed( bool checked );
    void menuEditOptionsPressed( bool checked );

    void menuViewZoomInPressed( bool checked );
    void menuViewZoomOutPressed( bool checked );
    void menuViewZoomOriginalPressed( bool checked );

    void menuHelpAboutPressed( bool checked );

    void menuAddLatexDocumentPressed();
    void menuAddSketchDocumentPressed();

    void toolbarCopyModeSelectorIndexChanged( const QString &copyMode );

    // For document compilation progress indicator
    void compilationStep( const QString &message, int step );
    void showProgressIndicator();

protected:
    virtual void closeEvent( QCloseEvent *event );
    virtual void resizeEvent( QResizeEvent *event );
    virtual void showEvent( QShowEvent *event );

public:
    MainWindow();
    ~MainWindow();
};

#endif // EQUATIONEDITOR_H
