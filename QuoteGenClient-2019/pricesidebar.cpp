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

void PriceSideBar::closeEvent (QCloseEvent *event)
{
    event->ignore();
    this->hide();
}
