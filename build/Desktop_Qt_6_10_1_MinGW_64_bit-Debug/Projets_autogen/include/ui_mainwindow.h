/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *titleInput;
    QLineEdit *artistInput;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *shuffleButton;
    QCheckBox *repeatButton;
    QPushButton *searchButton;
    QPushButton *moveButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        titleInput = new QLineEdit(centralwidget);
        titleInput->setObjectName("titleInput");

        verticalLayout->addWidget(titleInput);

        artistInput = new QLineEdit(centralwidget);
        artistInput->setObjectName("artistInput");

        verticalLayout->addWidget(artistInput);

        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");

        verticalLayout->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        addButton = new QPushButton(centralwidget);
        addButton->setObjectName("addButton");

        horizontalLayout->addWidget(addButton);

        removeButton = new QPushButton(centralwidget);
        removeButton->setObjectName("removeButton");

        horizontalLayout->addWidget(removeButton);

        shuffleButton = new QPushButton(centralwidget);
        shuffleButton->setObjectName("shuffleButton");

        horizontalLayout->addWidget(shuffleButton);

        repeatButton = new QCheckBox(centralwidget);
        repeatButton->setObjectName("repeatButton");

        horizontalLayout->addWidget(repeatButton);

        searchButton = new QPushButton(centralwidget);
        searchButton->setObjectName("searchButton");

        horizontalLayout->addWidget(searchButton);

        moveButton = new QPushButton(centralwidget);
        moveButton->setObjectName("moveButton");

        horizontalLayout->addWidget(moveButton);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestion de Playlist", nullptr));
        titleInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "Titre de la chanson", nullptr));
        artistInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nom de l'artiste", nullptr));
        addButton->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        removeButton->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        shuffleButton->setText(QCoreApplication::translate("MainWindow", "Lecture al\303\251atoire", nullptr));
        repeatButton->setText(QCoreApplication::translate("MainWindow", "R\303\251p\303\251tition", nullptr));
        searchButton->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        moveButton->setText(QCoreApplication::translate("MainWindow", "R\303\251organiser", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
