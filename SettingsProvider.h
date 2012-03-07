#ifndef SETTINGSPROVIDER_H
#define SETTINGSPROVIDER_H

#include <QSettings>
#include <QFont>

class SettingsProvider : public QObject
{
    Q_OBJECT

private:
    static SettingsProvider *m_Instance;
    QSettings *m_Settings;

    SettingsProvider();
    ~SettingsProvider();

public:
    static SettingsProvider * instance();

    // Compiler
    void setLatexBinary( const QString &path );
    void setDvisvgmBinary( const QString &path );
    QString latexBinary() const;
    QString dvisvgmBinary() const;

    // Preview
    void setPreviewScale( const qreal &scale );
    qreal previewScale() const;

    // Editor Font
    void setEditorFont( const QString &family, int pointSize );
    QFont editorFont() const;

    bool valid() const; // True if the settings are valid
    void setDirty();    // Call if our settings have been modified

signals:
    void configurationSettingsChanged();
};

#endif // SETTINGSPROVIDER_H
