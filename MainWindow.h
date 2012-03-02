#ifndef EQUATIONEDITOR_H
#define EQUATIONEDITOR_H

#include <QtGui>

#include "DocumentEditor.h"
#include "ErrorLog.h"
#include "SettingsDialog.h"

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

    // Document stuff
    DocumentEditor *m_ActiveDocument;
    ErrorLog *m_ErrorLog;

    SettingsProvider *m_Settings;    

    int m_TabCounter;

    void setupUserInterface();
    void setupToolbar();
    void addDocumentTab( const QString &name );
    void addAdderTab();

    QString generateEmptyTabName();

    void checkActiveDocumentStatus();
    void setStatusMessage( bool enabled, const QString &message = "", const QColor & color = QColor( 0, 0, 0 ));

private slots:
    void buttonCompilePressed( bool checked );
    void buttonErrorLogPressed( bool checked );
    void buttonCopyClipboardPressed( bool checked );
    void buttonAddDocumentEditorTabButtonPressed();

    void tabWidgetIndexChanged( int index );
    void tabCloseRequested( int index );
    void activeDocumentStatusChanged();

    void menuFileQuitPressed( bool checked );
    void menuEditOptionsPressed( bool checked );

    void menuViewZoomInPressed( bool checked );
    void menuViewZoomOutPressed( bool checked );
    void menuViewZoomOriginalPressed( bool checked );

    void toolbarCopyModeSelectorIndexChanged( const QString &copyMode );

public:
    MainWindow();
    ~MainWindow();   
};

#endif // EQUATIONEDITOR_H
