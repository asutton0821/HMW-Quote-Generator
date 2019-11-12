/********************************************************************************
** Form generated from reading UI file 'quotestatus.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUOTESTATUS_H
#define UI_QUOTESTATUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_QuoteStatus
{
public:
    QDialogButtonBox *buttonBox;
    QComboBox *statusComboBox;
    QLabel *label;
    QTableWidget *statusTableBox;
    QLabel *statusLabel;

    void setupUi(QDialog *QuoteStatus)
    {
        if (QuoteStatus->objectName().isEmpty())
            QuoteStatus->setObjectName(QString::fromUtf8("QuoteStatus"));
        QuoteStatus->resize(486, 387);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QuoteStatus->sizePolicy().hasHeightForWidth());
        QuoteStatus->setSizePolicy(sizePolicy);
        QuoteStatus->setSizeGripEnabled(false);
        buttonBox = new QDialogButtonBox(QuoteStatus);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(110, 330, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        statusComboBox = new QComboBox(QuoteStatus);
        statusComboBox->addItem(QString());
        statusComboBox->addItem(QString());
        statusComboBox->addItem(QString());
        statusComboBox->setObjectName(QString::fromUtf8("statusComboBox"));
        statusComboBox->setGeometry(QRect(220, 50, 71, 22));
        label = new QLabel(QuoteStatus);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(160, 50, 61, 21));
        statusTableBox = new QTableWidget(QuoteStatus);
        if (statusTableBox->columnCount() < 3)
            statusTableBox->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        statusTableBox->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        statusTableBox->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        statusTableBox->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        statusTableBox->setObjectName(QString::fromUtf8("statusTableBox"));
        statusTableBox->setGeometry(QRect(70, 100, 321, 201));
        statusTableBox->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        statusTableBox->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        statusTableBox->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        statusTableBox->setEditTriggers(QAbstractItemView::NoEditTriggers);
        statusTableBox->setSelectionMode(QAbstractItemView::SingleSelection);
        statusTableBox->setSelectionBehavior(QAbstractItemView::SelectRows);
        statusLabel = new QLabel(QuoteStatus);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setGeometry(QRect(80, 80, 331, 20));
        statusLabel->setAlignment(Qt::AlignCenter);

        retranslateUi(QuoteStatus);
        QObject::connect(buttonBox, SIGNAL(accepted()), QuoteStatus, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), QuoteStatus, SLOT(reject()));

        QMetaObject::connectSlotsByName(QuoteStatus);
    } // setupUi

    void retranslateUi(QDialog *QuoteStatus)
    {
        QuoteStatus->setWindowTitle(QApplication::translate("QuoteStatus", "Quote Status", nullptr));
        statusComboBox->setItemText(0, QApplication::translate("QuoteStatus", "Open", nullptr));
        statusComboBox->setItemText(1, QApplication::translate("QuoteStatus", "Closed", nullptr));
        statusComboBox->setItemText(2, QApplication::translate("QuoteStatus", "Expired", nullptr));

        label->setText(QApplication::translate("QuoteStatus", "Sort By", nullptr));
        QTableWidgetItem *___qtablewidgetitem = statusTableBox->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QuoteStatus", "Quote #", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = statusTableBox->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("QuoteStatus", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = statusTableBox->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("QuoteStatus", "Date", nullptr));
        statusLabel->setText(QApplication::translate("QuoteStatus", "PlaceHolder", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QuoteStatus: public Ui_QuoteStatus {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUOTESTATUS_H
