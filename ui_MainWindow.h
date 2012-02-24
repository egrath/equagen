/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Thu Feb 23 15:58:08 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionFileQuit;
    QAction *actionEditOptions;
    QAction *actionButtonCompile;
    QAction *actionButtonErrorLog;
    QAction *actionButtonCopyClipboard;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *buttonErrorLog;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonCopyClipboard;
    QPushButton *buttonCompile;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menu_Edit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(773, 674);
        actionFileQuit = new QAction(MainWindow);
        actionFileQuit->setObjectName(QString::fromUtf8("actionFileQuit"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/edit-logout.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionFileQuit->setIcon(icon);
        actionFileQuit->setIconVisibleInMenu(true);
        actionEditOptions = new QAction(MainWindow);
        actionEditOptions->setObjectName(QString::fromUtf8("actionEditOptions"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/preferences-system.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionEditOptions->setIcon(icon1);
        actionEditOptions->setIconVisibleInMenu(true);
        actionButtonCompile = new QAction(MainWindow);
        actionButtonCompile->setObjectName(QString::fromUtf8("actionButtonCompile"));
        actionButtonErrorLog = new QAction(MainWindow);
        actionButtonErrorLog->setObjectName(QString::fromUtf8("actionButtonErrorLog"));
        actionButtonCopyClipboard = new QAction(MainWindow);
        actionButtonCopyClipboard->setObjectName(QString::fromUtf8("actionButtonCopyClipboard"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setIconSize(QSize(16, 16));
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);

        verticalLayout->addWidget(tabWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        buttonErrorLog = new QPushButton(centralwidget);
        buttonErrorLog->setObjectName(QString::fromUtf8("buttonErrorLog"));
        buttonErrorLog->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/dialog-error.svg"), QSize(), QIcon::Normal, QIcon::On);
        buttonErrorLog->setIcon(icon2);

        horizontalLayout->addWidget(buttonErrorLog);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonCopyClipboard = new QPushButton(centralwidget);
        buttonCopyClipboard->setObjectName(QString::fromUtf8("buttonCopyClipboard"));
        buttonCopyClipboard->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/edit-redo.svg"), QSize(), QIcon::Normal, QIcon::On);
        buttonCopyClipboard->setIcon(icon3);

        horizontalLayout->addWidget(buttonCopyClipboard);

        buttonCompile = new QPushButton(centralwidget);
        buttonCompile->setObjectName(QString::fromUtf8("buttonCompile"));
        buttonCompile->setEnabled(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/go-next.svg"), QSize(), QIcon::Normal, QIcon::On);
        buttonCompile->setIcon(icon4);

        horizontalLayout->addWidget(buttonCompile);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 773, 24));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_Edit = new QMenu(menubar);
        menu_Edit->setObjectName(QString::fromUtf8("menu_Edit"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu_File->menuAction());
        menubar->addAction(menu_Edit->menuAction());
        menu_File->addAction(actionFileQuit);
        menu_Edit->addAction(actionEditOptions);

        retranslateUi(MainWindow);
        QObject::connect(buttonCompile, SIGNAL(clicked()), actionButtonCompile, SLOT(trigger()));
        QObject::connect(buttonErrorLog, SIGNAL(clicked()), actionButtonErrorLog, SLOT(trigger()));
        QObject::connect(buttonCopyClipboard, SIGNAL(clicked()), actionButtonCopyClipboard, SLOT(trigger()));

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Equator - LaTeX Snippet Editor", 0, QApplication::UnicodeUTF8));
        actionFileQuit->setText(QApplication::translate("MainWindow", "&Quit", 0, QApplication::UnicodeUTF8));
        actionEditOptions->setText(QApplication::translate("MainWindow", "&Options", 0, QApplication::UnicodeUTF8));
        actionButtonCompile->setText(QApplication::translate("MainWindow", "actionButtonCompile", 0, QApplication::UnicodeUTF8));
        actionButtonErrorLog->setText(QApplication::translate("MainWindow", "actionButtonErrorLog", 0, QApplication::UnicodeUTF8));
        actionButtonCopyClipboard->setText(QApplication::translate("MainWindow", "actionButtonCopyClipboard", 0, QApplication::UnicodeUTF8));
        buttonErrorLog->setText(QApplication::translate("MainWindow", "Error Log", 0, QApplication::UnicodeUTF8));
        buttonCopyClipboard->setText(QApplication::translate("MainWindow", "&Copy to Clipboard", 0, QApplication::UnicodeUTF8));
        buttonCompile->setText(QApplication::translate("MainWindow", "Com&pile", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menu_Edit->setTitle(QApplication::translate("MainWindow", "&Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
