/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 5.15.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QPushButton *ok;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *scroll;
    QWidget *scrollAreaWidgetContents;
    QPushButton *openImage;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(582, 425);
        ok = new QPushButton(Form);
        ok->setObjectName(QString::fromUtf8("ok"));
        ok->setGeometry(QRect(490, 10, 86, 30));
        verticalLayoutWidget = new QWidget(Form);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(-1, 0, 481, 423));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        scroll = new QScrollArea(verticalLayoutWidget);
        scroll->setObjectName(QString::fromUtf8("scroll"));
        scroll->setMaximumSize(QSize(800, 400));
        scroll->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 477, 398));
        scroll->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scroll);

        openImage = new QPushButton(Form);
        openImage->setObjectName(QString::fromUtf8("openImage"));
        openImage->setGeometry(QRect(490, 80, 86, 30));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        ok->setText(QCoreApplication::translate("Form", "\346\210\252\345\233\276", nullptr));
        openImage->setText(QCoreApplication::translate("Form", "\346\211\223\345\274\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
