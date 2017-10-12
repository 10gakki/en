/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_windowClass
{
public:

    void setupUi(QWidget *windowClass)
    {
        if (windowClass->objectName().isEmpty())
            windowClass->setObjectName(QStringLiteral("windowClass"));
        windowClass->resize(600, 400);

        retranslateUi(windowClass);

        QMetaObject::connectSlotsByName(windowClass);
    } // setupUi

    void retranslateUi(QWidget *windowClass)
    {
        windowClass->setWindowTitle(QApplication::translate("windowClass", "window", 0));
    } // retranslateUi

};

namespace Ui {
    class windowClass: public Ui_windowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
