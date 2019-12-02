#include "quotestatus.h"
#include "ui_quotestatus.h"
#include "mainwindow.h"
#include <QSystemTrayIcon>

QuoteStatus::QuoteStatus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuoteStatus)
{
    ui->setupUi(this);


    ui->statusTableBox->setSelectionBehavior( QAbstractItemView::SelectItems );
    //ui->statusTableBox->setSelectionMode( QAbstractItemView::SingleSelection );
    //connect(ui->buttonBox, SIGNAL(accepted()),this,SLOT(accept()));
    connect(ui->statusComboBox, SIGNAL(activated(int)),this,SLOT(begin()));
    connect(ui->statusTableBox,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(accept()));

    quoteNumberToGo = -1;

//486,387
    this->setFixedSize(QSize(486,387));
    ui->statusTableBox->verticalHeader()->setVisible(false);

    trayIcon = new QSystemTrayIcon (this);
    trayIcon->setIcon(QPixmap(":/img/hurdleicon.ico"));
    trayIcon ->setToolTip(tr("Hurdle"));
    trayIcon->show();

}

QuoteStatus::~QuoteStatus()
{
    delete ui;
}


void QuoteStatus::begin(){
    count();

if(ui->statusComboBox->currentText() == "Open"){
    sortBy("open");
}
if(ui->statusComboBox->currentText() == "Closed"){
    sortBy("closed");
}
if(ui->statusComboBox->currentText() == "Expired"){
    sortBy("expired");
}




}



/*
 *
 * The OK button is pressed, and will begin the process of "jumping" to a new quote
 * using the mouse move event in MainWindow.
 *
 */

void QuoteStatus::accept(){
    QModelIndexList list = ui->statusTableBox->selectionModel()->selectedIndexes();
    if (list.isEmpty()){ //Hides sidebar if presses ok and nothing selected
        this->hide();
    }
    else{
        int listRow = list.at(0).row();
        int quoteNum = ui->statusTableBox->item(listRow,0)->text().toInt();
        quoteNumberToGo = quoteNum;
        qDebug() << "jumping to quote number " << quoteNum;
    }


}

/*
 * Sorts the quotes in ascending order (1, 2, 3, etc)
 *
 */


void QuoteStatus::sortBy(QString sortType){
    if(sortType == "open"){
        update();
       // qDebug() << "sorting by open";
        addAllOpen();
    }
    if(sortType == "closed"){
        update();
      //  qDebug() << "sorting by closed";
        addAllClosed();
    }
    if(sortType == "expired"){
        update();
     //   qDebug() << "sorting by expired";
        addAllExpired();
    }


}

/*
 *
 * When the Cancel button is pressed, hide the Sidebar
 *
 */
void QuoteStatus::reject(){
    this->hide();
}

/*
 *
 * Show all the open items
 *
 */

void QuoteStatus::addAllOpen(){

    QSqlQuery q;
    int i = 0;
    bool openQuotesHaveSales = false;
    q.exec("SELECT quoteNum FROM `quoteTable` WHERE name = 'statusBox' AND value = 'Open'");
    while(q.next()){
        QSqlQuery qt;
        int quoteNum = q.value(0).toInt();
        ui->statusTableBox->insertRow(i);
        QTableWidgetItem * num = new QTableWidgetItem ();
        num->setData(Qt::DisplayRole,quoteNum);
        ui->statusTableBox->setItem(i,0,num);
        qt.exec("SELECT value FROM `quoteTable` WHERE name = 'nameLineEdit' AND quoteNum = "+QString::number(quoteNum));
        qt.last();
        QString names = qt.value(0).toString();
        QTableWidgetItem * name = new QTableWidgetItem (names);
        ui->statusTableBox->setItem(i,1,name);
        qt.exec("SELECT value FROM `quoteTable` WHERE name = 'dateEdit' AND quoteNum = "+QString::number(quoteNum));
        qt.last();
        QString dates = qt.value(0).toString();
        QTableWidgetItem * date = new QTableWidgetItem (dates);
        ui->statusTableBox->setItem(i,2,date);

        qt.exec("SELECT value FROM `quoteTable` WHERE name = 'dateEdit' AND quoteNum = "+QString::number(quoteNum));
        qt.last();

        i++;
    }
    ui->statusTableBox->sortItems(0,Qt::AscendingOrder);
    qDebug() << 'showing message';
    trayIcon->showMessage("Attention!","A New Quote has been added that requires attention",QSystemTrayIcon::Information,10000);


}

/*
 *
 * Show all the expired items
 *
 */

void QuoteStatus::addAllExpired(){

    QSqlQuery q;
    int i = 0;
    q.exec("SELECT quoteNum FROM `quoteTable` WHERE name = 'statusBox' AND value = 'Expired'");
    while(q.next()){
        QSqlQuery qt;
        int quoteNum = q.value(0).toInt();
        ui->statusTableBox->insertRow(i);
        QTableWidgetItem * num = new QTableWidgetItem ();
        num->setData(Qt::DisplayRole,quoteNum);
        ui->statusTableBox->setItem(i,0,num);
        qt.exec("SELECT value FROM `quoteTable` WHERE name = 'nameLineEdit' AND quoteNum = "+QString::number(quoteNum));
        qt.last();
        QString names = qt.value(0).toString();
        QTableWidgetItem * name = new QTableWidgetItem (names);
        ui->statusTableBox->setItem(i,1,name);
       qt.exec("SELECT value FROM `quoteTable` WHERE name = 'dateEdit' AND quoteNum = "+QString::number(quoteNum));
        qt.last();
        QString dates = qt.value(0).toString();
        QTableWidgetItem * date = new QTableWidgetItem (dates);
        ui->statusTableBox->setItem(i,2,date);
        i++;
    }
    ui->statusTableBox->sortItems(0,Qt::AscendingOrder);


}
/*
 *
 * Show all the closed items
 *
 */

void QuoteStatus::addAllClosed(){

    QSqlQuery q;
    int i = 0;
    q.exec("SELECT quoteNum FROM `quoteTable` WHERE name = 'statusBox' AND value = 'Closed'");
    while(q.next()){
        QSqlQuery qt;
        int quoteNum = q.value(0).toInt();
        ui->statusTableBox->insertRow(i);
        QTableWidgetItem * num = new QTableWidgetItem ();
        num->setData(Qt::DisplayRole,quoteNum);
        ui->statusTableBox->setItem(i,0,num);
         qt.exec("SELECT value FROM `quoteTable` WHERE name = 'nameLineEdit' AND quoteNum = "+QString::number(quoteNum));
        qt.last();
        QString names = qt.value(0).toString();
        QTableWidgetItem * name = new QTableWidgetItem (names);
        ui->statusTableBox->setItem(i,1,name);
        qt.exec("SELECT value FROM `quoteTable` WHERE name = 'dateEdit' AND quoteNum = "+QString::number(quoteNum));
        qt.last();
        QString dates = qt.value(0).toString();
        QTableWidgetItem * date = new QTableWidgetItem (dates);
        ui->statusTableBox->setItem(i,2,date);
        i++;
    }
    ui->statusTableBox->sortItems(0,Qt::AscendingOrder);


}
/*
 *
 * Update the rows by removing row 0 until no more rows exist.
 *
 */

void QuoteStatus::update(){
   // ui->statusTableBox->clear();
    while (ui->statusTableBox->rowCount() > 0)
    {
       ui->statusTableBox->removeRow(0);
    }

  //  ui->statusTableBox->removeRow(0);
}

/*
 *
 * Count the number of objects in each category.
 *
 */

void QuoteStatus::count(){
    int open =0,closed = 0, expired = 0;
    QSqlQuery qu;
    qu.exec("SELECT quoteNum FROM `quoteTable` WHERE name = 'statusBox' AND value = 'Open' ");
    qu.last();
    if(qu.at() > -1){
      open = qu.at() + 1;
    }

    qu.exec("SELECT quoteNum FROM `quoteTable` WHERE name = 'statusBox' AND value = 'Closed' ");
    qu.last();
    if(qu.at() > -1){
       closed = qu.at() + 1;
    }

    qu.exec("SELECT quoteNum FROM `quoteTable` WHERE name = 'statusBox' AND value = 'Expired' ");
    qu.last();
    if(qu.at() > -1){
        expired = qu.at() + 1;
    }

    ui->statusLabel->setText("Quotes: "+QString::number(open)+" open, "+QString::number(closed)+" closed, and "+QString::number(expired)+ " expired");




}


