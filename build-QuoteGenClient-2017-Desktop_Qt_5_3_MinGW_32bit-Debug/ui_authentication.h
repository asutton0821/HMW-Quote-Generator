/********************************************************************************
** Form generated from reading UI file 'authentication.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHENTICATION_H
#define UI_AUTHENTICATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_authentication
{
public:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QLabel *authenticationStatusLabel;
    QLabel *usernameLabel;
    QLabel *passwordLabel;
    QLabel *label_logo;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *authentication)
    {
        if (authentication->objectName().isEmpty())
            authentication->setObjectName(QStringLiteral("authentication"));
        authentication->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(authentication->sizePolicy().hasHeightForWidth());
        authentication->setSizePolicy(sizePolicy);
        usernameLineEdit = new QLineEdit(authentication);
        usernameLineEdit->setObjectName(QStringLiteral("usernameLineEdit"));
        usernameLineEdit->setGeometry(QRect(152, 80, 161, 22));
        passwordLineEdit = new QLineEdit(authentication);
        passwordLineEdit->setObjectName(QStringLiteral("passwordLineEdit"));
        passwordLineEdit->setGeometry(QRect(150, 130, 161, 22));
        passwordLineEdit->setEchoMode(QLineEdit::Password);
        authenticationStatusLabel = new QLabel(authentication);
        authenticationStatusLabel->setObjectName(QStringLiteral("authenticationStatusLabel"));
        authenticationStatusLabel->setGeometry(QRect(120, 190, 201, 20));
        usernameLabel = new QLabel(authentication);
        usernameLabel->setObjectName(QStringLiteral("usernameLabel"));
        usernameLabel->setGeometry(QRect(70, 80, 71, 20));
        passwordLabel = new QLabel(authentication);
        passwordLabel->setObjectName(QStringLiteral("passwordLabel"));
        passwordLabel->setGeometry(QRect(70, 130, 71, 20));
        label_logo = new QLabel(authentication);
        label_logo->setObjectName(QStringLiteral("label_logo"));
        label_logo->setGeometry(QRect(140, 10, 131, 51));
        label_logo->setPixmap(QPixmap(QString::fromUtf8(":/img/img/simplelogo2.jpg")));
        label_logo->setScaledContents(true);
        okButton = new QPushButton(authentication);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(120, 240, 75, 23));
        cancelButton = new QPushButton(authentication);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(210, 240, 75, 23));

        retranslateUi(authentication);

        QMetaObject::connectSlotsByName(authentication);
    } // setupUi

    void retranslateUi(QDialog *authentication)
    {
        authentication->setWindowTitle(QApplication::translate("authentication", "Dialog", 0));
        authenticationStatusLabel->setText(QApplication::translate("authentication", "AuthenticationStatusLabel", 0));
        usernameLabel->setText(QApplication::translate("authentication", "Username:", 0));
        passwordLabel->setText(QApplication::translate("authentication", "Password:", 0));
        label_logo->setText(QString());
        okButton->setText(QApplication::translate("authentication", "Ok", 0));
        cancelButton->setText(QApplication::translate("authentication", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class authentication: public Ui_authentication {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHENTICATION_H
