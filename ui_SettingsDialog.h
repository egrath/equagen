/********************************************************************************
** Form generated from reading UI file 'SettingsDialog.ui'
**
** Created: Wed Feb 22 14:05:02 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tabGeneral_2;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QLineEdit *textEditLatex;
    QPushButton *buttonBrowseLatex;
    QLabel *label_5;
    QLineEdit *textEditDvipng;
    QPushButton *buttonBrowseDvipng;
    QSpacerItem *verticalSpacer_2;
    QLineEdit *textEditDvisvgm;
    QPushButton *buttonBrowseDvisvgm;
    QLabel *label_6;
    QWidget *tabFonts_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *buttonSave;
    QPushButton *buttonCancel;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QString::fromUtf8("SettingsDialog"));
        SettingsDialog->setWindowModality(Qt::WindowModal);
        SettingsDialog->resize(419, 252);
        verticalLayout = new QVBoxLayout(SettingsDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(SettingsDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabGeneral_2 = new QWidget();
        tabGeneral_2->setObjectName(QString::fromUtf8("tabGeneral_2"));
        gridLayout_2 = new QGridLayout(tabGeneral_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_4 = new QLabel(tabGeneral_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        textEditLatex = new QLineEdit(tabGeneral_2);
        textEditLatex->setObjectName(QString::fromUtf8("textEditLatex"));

        gridLayout_2->addWidget(textEditLatex, 0, 1, 1, 1);

        buttonBrowseLatex = new QPushButton(tabGeneral_2);
        buttonBrowseLatex->setObjectName(QString::fromUtf8("buttonBrowseLatex"));

        gridLayout_2->addWidget(buttonBrowseLatex, 0, 2, 1, 1);

        label_5 = new QLabel(tabGeneral_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        textEditDvipng = new QLineEdit(tabGeneral_2);
        textEditDvipng->setObjectName(QString::fromUtf8("textEditDvipng"));

        gridLayout_2->addWidget(textEditDvipng, 1, 1, 1, 1);

        buttonBrowseDvipng = new QPushButton(tabGeneral_2);
        buttonBrowseDvipng->setObjectName(QString::fromUtf8("buttonBrowseDvipng"));

        gridLayout_2->addWidget(buttonBrowseDvipng, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 3, 1, 1, 1);

        textEditDvisvgm = new QLineEdit(tabGeneral_2);
        textEditDvisvgm->setObjectName(QString::fromUtf8("textEditDvisvgm"));

        gridLayout_2->addWidget(textEditDvisvgm, 2, 1, 1, 1);

        buttonBrowseDvisvgm = new QPushButton(tabGeneral_2);
        buttonBrowseDvisvgm->setObjectName(QString::fromUtf8("buttonBrowseDvisvgm"));

        gridLayout_2->addWidget(buttonBrowseDvisvgm, 2, 2, 1, 1);

        label_6 = new QLabel(tabGeneral_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        tabWidget->addTab(tabGeneral_2, QString());
        tabFonts_2 = new QWidget();
        tabFonts_2->setObjectName(QString::fromUtf8("tabFonts_2"));
        tabWidget->addTab(tabFonts_2, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        buttonSave = new QPushButton(SettingsDialog);
        buttonSave->setObjectName(QString::fromUtf8("buttonSave"));

        horizontalLayout_2->addWidget(buttonSave);

        buttonCancel = new QPushButton(SettingsDialog);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));

        horizontalLayout_2->addWidget(buttonCancel);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(SettingsDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "Application settings", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SettingsDialog", "latex", 0, QApplication::UnicodeUTF8));
        buttonBrowseLatex->setText(QApplication::translate("SettingsDialog", "Browse", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("SettingsDialog", "dvipng", 0, QApplication::UnicodeUTF8));
        buttonBrowseDvipng->setText(QApplication::translate("SettingsDialog", "Browse", 0, QApplication::UnicodeUTF8));
        buttonBrowseDvisvgm->setText(QApplication::translate("SettingsDialog", "Browse", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("SettingsDialog", "dvisvgm", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabGeneral_2), QApplication::translate("SettingsDialog", "Paths", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabFonts_2), QApplication::translate("SettingsDialog", "Fonts", 0, QApplication::UnicodeUTF8));
        buttonSave->setText(QApplication::translate("SettingsDialog", "Save", 0, QApplication::UnicodeUTF8));
        buttonCancel->setText(QApplication::translate("SettingsDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
