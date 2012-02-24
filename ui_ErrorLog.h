/********************************************************************************
** Form generated from reading UI file 'ErrorLog.ui'
**
** Created: Wed Feb 22 14:05:02 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERRORLOG_H
#define UI_ERRORLOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ErrorLog
{
public:
    QAction *actionButtonClose;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *textEditErrorLog;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonClose;

    void setupUi(QWidget *ErrorLog)
    {
        if (ErrorLog->objectName().isEmpty())
            ErrorLog->setObjectName(QString::fromUtf8("ErrorLog"));
        ErrorLog->resize(800, 572);
        actionButtonClose = new QAction(ErrorLog);
        actionButtonClose->setObjectName(QString::fromUtf8("actionButtonClose"));
        verticalLayout = new QVBoxLayout(ErrorLog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textEditErrorLog = new QPlainTextEdit(ErrorLog);
        textEditErrorLog->setObjectName(QString::fromUtf8("textEditErrorLog"));
        textEditErrorLog->setReadOnly(true);

        verticalLayout->addWidget(textEditErrorLog);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonClose = new QPushButton(ErrorLog);
        buttonClose->setObjectName(QString::fromUtf8("buttonClose"));

        horizontalLayout->addWidget(buttonClose);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ErrorLog);
        QObject::connect(buttonClose, SIGNAL(clicked()), actionButtonClose, SLOT(trigger()));

        QMetaObject::connectSlotsByName(ErrorLog);
    } // setupUi

    void retranslateUi(QWidget *ErrorLog)
    {
        ErrorLog->setWindowTitle(QApplication::translate("ErrorLog", "Error Log", 0, QApplication::UnicodeUTF8));
        actionButtonClose->setText(QApplication::translate("ErrorLog", "actionButtonClose", 0, QApplication::UnicodeUTF8));
        buttonClose->setText(QApplication::translate("ErrorLog", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ErrorLog: public Ui_ErrorLog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERRORLOG_H
