/********************************************************************************
** Form generated from reading UI file 'serverscreen.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERSCREEN_H
#define UI_SERVERSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerScreen
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ServerScreen)
    {
        if (ServerScreen->objectName().isEmpty())
            ServerScreen->setObjectName(QStringLiteral("ServerScreen"));
        ServerScreen->resize(400, 300);
        menuBar = new QMenuBar(ServerScreen);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ServerScreen->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ServerScreen);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ServerScreen->addToolBar(mainToolBar);
        centralWidget = new QWidget(ServerScreen);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ServerScreen->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ServerScreen);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ServerScreen->setStatusBar(statusBar);

        retranslateUi(ServerScreen);

        QMetaObject::connectSlotsByName(ServerScreen);
    } // setupUi

    void retranslateUi(QMainWindow *ServerScreen)
    {
        ServerScreen->setWindowTitle(QApplication::translate("ServerScreen", "ServerScreen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ServerScreen: public Ui_ServerScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERSCREEN_H
