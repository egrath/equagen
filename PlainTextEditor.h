#ifndef PLAINTEXTEDITOR_H
#define PLAINTEXTEDITOR_H

#include <QtGui>

class PlainTextEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    PlainTextEditor( QWidget *parent = 0 );
    virtual ~PlainTextEditor();
};

#endif // PLAINTEXTEDITOR_H
