#ifndef SETTINGSPROVIDER_H
#define SETTINGSPROVIDER_H

#include <QSettings>

class SettingsProvider
{
private:
    static SettingsProvider *m_Instance;
    QSettings *m_Settings;

    SettingsProvider();
    ~SettingsProvider();

public:
    static SettingsProvider * getInstance();

    // Compiler
    void setLatexBinary( const QString &path );
    void setDvipngBinary( const QString &path );
    void setDvisvgmBinary( const QString &path );
    QString latexBinary() const;
    QString dvipngBinary() const;
    QString dvisvgmBinary() const;

    // Preview
    void setPreviewScale( const qreal &scale );
    qreal previewScale() const;

    bool valid() const; // True if the settings are valid
};

#endif // SETTINGSPROVIDER_H
