#include "PlainTextEditor.h"

PlainTextEditor::PlainTextEditor( QWidget *parent ) : QPlainTextEdit( parent )
{
    qDebug() << "PlainTextEditor::ctor";
}

PlainTextEditor::~PlainTextEditor()
{
}

