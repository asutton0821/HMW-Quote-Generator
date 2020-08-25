#include "customerinfo.h"
#include "ui_customerinfo.h"

customerInfo::customerInfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::customerInfo)
{
    ui->setupUi(this);


    ui->customerInfoTableBox->verticalHeader()->setVisible(false);
this->setFixedSize(QSize(1127,821));

    addContacts();


    connect(ui->copyPushButton, SIGNAL(clicked()),this,SLOT(copyButtonPushed()));
    connect(ui->deletePushButton,SIGNAL(clicked()),this,SLOT(deleteButtonPushed()));
    connect(ui->customerInfoTableBox, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(edited(QTableWidgetItem *)));
    connect(ui->searchLineEdit, SIGNAL(textEdited(QString)), this, SLOT(search(QString)));


}
/*
 * Adds a contact to the databse, which is then displayed on the board using the MainWindow function call.
 *
 */

void customerInfo::addContact(QString name, QString company, QString a1, QString a2, QString city, QString state, QString zip, QString email, QString fax, QString phone1, QString phone2){
    QSqlQuery qu;
    qu.prepare("INSERT INTO `Contacts` VALUES (:name, :company, :address1, :address2, :city, :state, :zip, :email, :fax, :phone1, :phone2, :notes, :specialAttribute) ");
    qu.bindValue(":name",name);
    qu.bindValue(":company",company);
    qu.bindValue(":address1",a1);
    qu.bindValue(":address2",a2);
    qu.bindValue(":city",city);
    qu.bindValue(":state",state);
    qu.bindValue(":zip",zip);
    qu.bindValue(":email",email);
    qu.bindValue(":fax",fax);
    qu.bindValue(":phone1",phone1);
    qu.bindValue(":phone2",phone2);
    qu.bindValue(":notes","Made from Quote Generator Automatically");
    qu.bindValue(":specialAttribute",0); //1 for vendor 0 for customer


   //qDebug() << " added contact? " << qu.exec() << qu.lastError();
   qu.exec();

}
/*
 * Detects editing and will update the contact in the database accordingly.
 *
 * You can see that this function will also be called each time a contact is added. To prevent this, we call blockSignals in the add contacts function. See "addContacts()" medthod.
 *
 *
 */
void customerInfo::edited(QTableWidgetItem * w){
   // qDebug() << "Row is " << w->row() << " and column is " << w->column() << " THe contact name = " << ui->customerInfoTableBox->item(w->row(),0)->text();
    QString name = ui->customerInfoTableBox->item(w->row(),0)->text();




    QSqlQuery qu;
    qu.exec("SELECT * FROM `Contacts` WHERE name = '"+name+"'");
    qu.last();
   // qDebug() << "SELECTED NAME OF " << qu.value(0).toString();



   // qDebug() << "editing happened at " << w->row() << " and " << w->column();
    qu.prepare("UPDATE  `Contacts` SET `name`=:name, `company`=:company, `address1`=:address1, `address2`=:address2, `city`=:city, `state`=:state, `zip`=:zip, `email`=:email, `fax`=:fax, `phone1`=:phone1, `phone2`=:phone2, `notes`=:notes, `specialAttribute`=:specialAttribute WHERE name = '"+name+"'");
    qu.bindValue(":name",ui->customerInfoTableBox->item(w->row(),0)->text());
    qu.bindValue(":company",ui->customerInfoTableBox->item(w->row(),1)->text());
    qu.bindValue(":address1",ui->customerInfoTableBox->item(w->row(),2)->text());
    qu.bindValue(":address2",ui->customerInfoTableBox->item(w->row(),3)->text());
    qu.bindValue(":city",ui->customerInfoTableBox->item(w->row(),4)->text());
    qu.bindValue(":state",ui->customerInfoTableBox->item(w->row(),5)->text());
    qu.bindValue(":zip",ui->customerInfoTableBox->item(w->row(),6)->text());
    qu.bindValue(":email",ui->customerInfoTableBox->item(w->row(),7)->text());
    qu.bindValue(":fax",ui->customerInfoTableBox->item(w->row(),8)->text());
    qu.bindValue(":phone1",ui->customerInfoTableBox->item(w->row(),9)->text());
    qu.bindValue(":phone2",ui->customerInfoTableBox->item(w->row(),10)->text());
    qu.bindValue(":notes","Made from Quote Generator Automatically");
    qu.bindValue(":specialAttribute",0); //1 for vendor 0 for customer
  //  qDebug() << qu.exec();
    qu.exec();







}

customerInfo::~customerInfo()
{
    delete ui;
}

/*
 *  Takes the list of contacts stored in the SQL Database and displays them on the screen.
 *
 */


void customerInfo::addContacts(){

  //  qDebug() << "This is a test";
    clear(); //clears the board
    ui->customerInfoTableBox->blockSignals(true);

    QSqlQuery query;
    query.exec("SELECT * FROM `Contacts`");


    int i = 0; // the number of things in table
    int j = 0;  //columns


    while(query.next()){
        ui->customerInfoTableBox->insertRow(i);
        while(j < 11){
            QTableWidgetItem * des = new QTableWidgetItem ();
            QString description = query.value(j).toString();
            des->setData(Qt::DisplayRole,description);
            ui->customerInfoTableBox->setItem(i,j,des);
            j++;
        }
        i++;
        j = 0;
    }


ui->customerInfoTableBox->blockSignals(false);
ui->customerInfoTableBox->sortItems(0,Qt::AscendingOrder);

}

/*
 * Copies the currently highlighted contact to the quote.
 *
 */


void customerInfo::copyButtonPushed(){
  //  qDebug() << "pushed";




    QModelIndexList list = ui->customerInfoTableBox->selectionModel()->selectedIndexes();
    int listRow = list.at(0).row();

    if(!list.isEmpty()){
        for(int y = 0; y < 11; y++){
           QString test = ui->customerInfoTableBox->item(listRow,y)->text();
           stringList.append(test);
        }
       // qDebug() << stringList;

    }


}

/*
 *
 *
 * This checks to make sure that a contact exists. Returns true or false based on existential state.
 *
 */

bool customerInfo::checkContactExist(QString name){
    QSqlQuery query;
    query.exec("SELECT * FROM `Contacts` WHERE name = '"+name+"'");
    query.last();
    if(query.value(0).isNull()){
        return false;
    }
    else{
        return true;
    }



}



/*
 * Clears the entire board.
 *
 */

void customerInfo::clear(){

       // ui->statusTableBox->clear();
          ui->customerInfoTableBox->blockSignals(true);
        while (ui->customerInfoTableBox->rowCount() > 0)
        {
           ui->customerInfoTableBox->removeRow(0);
        }
        ui->customerInfoTableBox->blockSignals(false);




}



/*
 * Deletes a contact based off the highlighted selection.
 *
 */


void customerInfo::deleteButtonPushed(){
    QModelIndexList list = ui->customerInfoTableBox->selectionModel()->selectedIndexes();
    int listRow = list.at(0).row();

    if(!list.isEmpty()){


        QSqlQuery query;
        qDebug() << query.exec("DELETE FROM `Contacts` WHERE name = '"+ui->customerInfoTableBox->item(listRow,0)->text()+"'");

        clear();
        addContacts();

    }


}


/*
 *
 * Allows you to search within the contacts app.
 * Creates a string and finds any type of query values in the name field (may modify this in the future) that contains the substring created.
 * if so, it displays only those rows.
 * If not, it displays nothing. To display all the objects again, simply clear the text field.
 *
 * Note: could be modified in the future to have a scope based on company name, name, address, etc. or you could do one "global" search of all the fields.
 * Would be nice to highlight the fields if so.
 *
 */

void customerInfo::search(QString text){
    if(text != "" && text != " "){
        QString lowerText = text.toLower();
       // qDebug() <<"text  " << lowerText;




        clear(); //clears the board
        ui->customerInfoTableBox->blockSignals(true);

        QSqlQuery query;
        if(SEARCHALLFIELDS){
           qDebug() << query.exec("SELECT * FROM `Contacts` WHERE `name` LIKE '%"+lowerText+"%' OR `company` LIKE '%"+lowerText+"%' OR `address1` LIKE '%"+lowerText+"%' OR `address2` LIKE '%"+lowerText+"%' OR `city` LIKE '%"+lowerText+"%' OR `state` LIKE '%"+lowerText+"%' OR `zip` LIKE '%"+lowerText+"%' OR `phone1` LIKE '%"+lowerText+"%' OR `phone2` LIKE '%"+lowerText+"%' OR `email` LIKE '%"+lowerText+"%' OR `fax` LIKE '%"+lowerText+"%'");
        }
        else{
            query.exec("SELECT * FROM `Contacts` WHERE `name` LIKE '%"+lowerText+"%'");
        }


        int i = 0; // the number of things in table
        int j = 0;  //columns


        while(query.next()){
            ui->customerInfoTableBox->insertRow(i);
            while(j < 11){
                QTableWidgetItem * des = new QTableWidgetItem ();
                QString description = query.value(j).toString();

                des->setData(Qt::DisplayRole,description);
                ui->customerInfoTableBox->setItem(i,j,des);

                if(SEARCHALLFIELDS && description.toLower().contains(lowerText)){
                    ui->customerInfoTableBox->item(i,j)->setTextColor(QColor(0,255,0));

                }
                if(!SEARCHALLFIELDS){
                    ui->customerInfoTableBox->item(i,0)->setTextColor(QColor(255,0,0));
                }

                j++;
            }
            i++;
            j = 0;
        }



    ui->customerInfoTableBox->blockSignals(false);
    ui->customerInfoTableBox->sortItems(0,Qt::AscendingOrder);

    }
    else{
        addContacts();
         ui->customerInfoTableBox->blockSignals(false);
    }
    ui->customerInfoTableBox->blockSignals(false);
}

void customerInfo::closeEvent (QCloseEvent *event)
{
    event->ignore();
    this->hide();
}



