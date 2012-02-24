/********************************************************************************
** Form generated from reading UI file 'DocumentEditor.ui'
**
** Created: Thu Feb 23 16:21:32 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCUMENTEDITOR_H
#define UI_DOCUMENTEDITOR_H

#include <PlainTextEditor.h>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QScrollArea>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <Renderer.h>

QT_BEGIN_NAMESPACE

class Ui_DocumentEditor
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea;
    Renderer *renderer;
    PlainTextEditor *textEditTex;

    void setupUi(QWidget *DocumentEditor)
    {
        if (DocumentEditor->objectName().isEmpty())
            DocumentEditor->setObjectName(QString::fromUtf8("DocumentEditor"));
        DocumentEditor->resize(718, 566);
        verticalLayout = new QVBoxLayout(DocumentEditor);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        scrollArea = new QScrollArea(DocumentEditor);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setStyleSheet(QString::fromUtf8("QScrollArea { background-color: rgb(255, 255, 255); }"));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignCenter);
        renderer = new Renderer();
        renderer->setObjectName(QString::fromUtf8("renderer"));
        renderer->setGeometry(QRect(0, 0, 696, 346));
        scrollArea->setWidget(renderer);

        horizontalLayout->addWidget(scrollArea);


        verticalLayout->addLayout(horizontalLayout);

        textEditTex = new PlainTextEditor(DocumentEditor);
        textEditTex->setObjectName(QString::fromUtf8("textEditTex"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEditTex->sizePolicy().hasHeightForWidth());
        textEditTex->setSizePolicy(sizePolicy);
        textEditTex->setMinimumSize(QSize(0, 192));
        textEditTex->setMaximumSize(QSize(16777215, 192));
        textEditTex->setBaseSize(QSize(0, 192));

        verticalLayout->addWidget(textEditTex);


        retranslateUi(DocumentEditor);

        QMetaObject::connectSlotsByName(DocumentEditor);
    } // setupUi

    void retranslateUi(QWidget *DocumentEditor)
    {
        DocumentEditor->setWindowTitle(QApplication::translate("DocumentEditor", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DocumentEditor: public Ui_DocumentEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCUMENTEDITOR_H
