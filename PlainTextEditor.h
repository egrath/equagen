#ifndef PLAINTEXTEDITOR_H
#define PLAINTEXTEDITOR_H

#include <QtGui>
#include "SettingsProvider.h"
#include "Debug.h"

class PlainTextEditor : public QPlainTextEdit
{
    Q_OBJECT

private:
    SettingsProvider *m_Settings;

private slots:
    void configurationSettingsChanged();

public:
    PlainTextEditor( QWidget *parent = 0 );
    virtual ~PlainTextEditor();
};

#endif // PLAINTEXTEDITOR_H
