/********************************************************************************
** Form generated from reading UI file 'quotestatus.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUOTESTATUS_H
#define UI_QUOTESTATUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
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
            QuoteStatus->setObjectName(QStringLiteral("QuoteStatus"));
        QuoteStatus->resize(486, 387);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QuoteStatus->sizePolicy().hasHeightForWidth());
        QuoteStatus->setSizePolicy(sizePolicy);
        QuoteStatus->setSizeGripEnabled(false);
        buttonBox = new QDialogButtonBox(QuoteStatus);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(110, 330, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        statusComboBox = new QComboBox(QuoteStatus);
        statusComboBox->setObjectName(QStringLiteral("statusComboBox"));
        statusComboBox->setGeometry(QRect(220, 50, 71, 22));
        label = new QLabel(QuoteStatus);
        label->setObjectName(QStringLiteral("label"));
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
        statusTableBox->setObjectName(QStringLiteral("statusTableBox"));
        statusTableBox->setGeometry(QRect(70, 100, 321, 201));
        statusTableBox->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        statusTableBox->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        statusTableBox->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        statusTableBox->setEditTriggers(QAbstractItemView::NoEditTriggers);
        statusTableBox->setSelectionMode(QAbstractItemView::SingleSelection);
        statusTableBox->setSelectionBehavior(QAbstractItemView::SelectRows);
        statusLabel = new QLabel(QuoteStatus);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        statusLabel->setGeometry(QRect(80, 80, 331, 20));
        statusLabel->setAlignment(Qt::AlignCenter);

        retranslateUi(QuoteStatus);
        QObject::connect(buttonBox, SIGNAL(accepted()), QuoteStatus, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), QuoteStatus, SLOT(reject()));

        QMetaObject::connectSlotsByName(QuoteStatus);
    } // setupUi

    void retranslateUi(QDialog *QuoteStatus)
    {
        QuoteStatus->setWindowTitle(QApplication::translate("QuoteStatus", "Quote Status", 0));
        statusComboBox->clear();
        statusComboBox->insertItems(0, QStringList()
         << QApplication::translate("QuoteStatus", "Open", 0)
         << QApplication::translate("QuoteStatus", "Closed", 0)
         << QApplication::translate("QuoteStatus", "Expired", 0)
        );
        label->setText(QApplication::translate("QuoteStatus", "Sort By", 0));
        QTableWidgetItem *___qtablewidgetitem = statusTableBox->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QuoteStatus", "Quote #", 0));
        QTableWidgetItem *___qtablewidgetitem1 = statusTableBox->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("QuoteStatus", "Name", 0));
        QTableWidgetItem *___qtablewidgetitem2 = statusTableBox->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("QuoteStatus", "Date", 0));
        statusLabel->setText(QApplication::translate("QuoteStatus", "PlaceHolder", 0));
    } // retranslateUi

};

namespace Ui {
    class QuoteStatus: public Ui_QuoteStatus {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUOTESTATUS_H
