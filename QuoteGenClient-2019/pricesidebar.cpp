#include "pricesidebar.h"
#include "ui_pricesidebar.h"

PriceSideBar::PriceSideBar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PriceSideBar)
{
    ui->setupUi(this);
   // ui->pricesTableBox->setSelectionBehavior( QAbstractItemView::SelectItems );
    getNameAndPrices();

    ui->pricesTableBox->verticalHeader()->setVisible(false);
this->setFixedSize(QSize(500,550));


}

PriceSideBar::~PriceSideBar()
{
    delete ui;
}

void PriceSideBar::getNameAndPrices(){

    QSqlQuery q;
    int i = 0;
    q.exec("SELECT * FROM `quoteItems`");
    while(q.next()){

        QString description = q.value(1).toString();
        ui->pricesTableBox->insertRow(i);
        if(description == "Wheel Size"){

            description = "Wheel Size 12";
            QTableWidgetItem * des = new QTableWidgetItem ();
            des->setData(Qt::DisplayRole,description);
            ui->pricesTableBox->setItem(i,0,des);
            int price = 1000;
            QTableWidgetItem * prices = new QTableWidgetItem ();
            prices->setData(Qt::DisplayRole,price);
            ui->pricesTableBox->setItem(i,1,prices);
            i++;

            QString description2 = "Wheel Size 14";
            QTableWidgetItem * des2 = new QTableWidgetItem ();
            des2->setData(Qt::DisplayRole,description2);
            ui->pricesTableBox->setItem(i,0,des2);
            int price2 = 1500;
            QTableWidgetItem * prices2 = new QTableWidgetItem ();
            prices2->setData(Qt::DisplayRole,price2);
            ui->pricesTableBox->setItem(i,1,prices2);
            i++;
            //qDebug() << "MADE IT TO 14 WOOH";



        }


        QTableWidgetItem * des = new QTableWidgetItem ();
        des->setData(Qt::DisplayRole,description);
        ui->pricesTableBox->setItem(i,0,des);
        int price = q.value(2).toInt();
        QTableWidgetItem * prices = new QTableWidgetItem ();
        prices->setData(Qt::DisplayRole,price);
        ui->pricesTableBox->setItem(i,1,prices);
        i++;
    }
    ui->pricesTableBox->sortItems(0,Qt::AscendingOrder);
    ui->pricesTableBox->setColumnWidth(0,300);
    ui->pricesTableBox->setColumnWidth(1,150);










}
