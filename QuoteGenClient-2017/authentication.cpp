#include "authentication.h"
#include "ui_authentication.h"
#include <QApplication>
#include <QMessageBox>

/*
 *
 * Opens the database for authentication
 *
 */

authentication::authentication(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authentication)
{
    ui->setupUi(this);

    QString dbAddress = "localhost";

    this->setFixedSize(QSize(400,300));
    buttonPressed = 0;
    ui->authenticationStatusLabel->setText("");
     frozen = true;
     bool mySql;

 //connect(ui->okCancelButtonBox,SIGNAL(rejected()),this,SLOT(reject()));
 connect(ui->cancelButton,SIGNAL(pressed()),this,SLOT(reject()));
 connect(ui->okButton,SIGNAL(pressed()),this,SLOT(accept()));

 this->setWindowTitle("Hurdle Machine Works Authentication");

 mySql = true;

 if(mySql == false){
QFile::exists("quotedatabase.sqlite");
 db = QSqlDatabase::addDatabase("QSQLITE");
 db.setDatabaseName("C:/Users/Colson/Desktop/quotedatabase.sqlite");
 bool opened = db.open();
 db.tables();
// qDebug() << getNumQuotes();
 }

 else{
 db = QSqlDatabase::addDatabase("QMYSQL");
 db.setDatabaseName("quotedatabase");
 db.setHostName(dbAddress);
 db.setPassword("password");
 db.setUserName("admin");
qDebug() << "Database open? : " << db.open();

if(db.open() == false){
    qDebug() << "Database does not exist";
    QMessageBox::critical(this,"Fatal Error", "A fatal has occured (100): No connection to the database could be established. Aborting. See log for details.");
    writeToLog("fatalcrash",QDate::currentDate().toString()+" at "+QTime::currentTime().toString()+": A fatal error occured. No connection could be made to the database address of "+dbAddress+" please check your internet configuration, and restart the program.");
    this->reject();
    qApp->exit(100);
   }
else{
    writeToLog("databaseconnected","A successful connection was made to "+dbAddress);

}


 }


}

authentication::~authentication()
{
    delete ui;
}

void authentication::writeToLog(QString name, QString data){
        QString logData = data;
        QString fileName = ""+name+"_"+QDate::currentDate().toString()+"_"+QTime::currentTime().toString();
        QFile file(fileName);
        //file.remove();
        if(file.open(QIODevice::ReadWrite)){
            QTextStream stream(&file);
            stream << logData << endl;

        }
        file.close();
}

/*
 *
 * Gets the number of users in the database
 *
 */


int authentication::getUserNum(){
    QSqlQuery query;
     query.exec("SELECT * FROM authentication");
     query.last();
   //qDebug() << "Quotes: " << query.at() + 1;

     if(query.at() > 0){
        return query.at() + 1;
     }
     if(query.at() == 0){
         return 1;
     }
     return 1;

}

/*
 *
 * Returns buttonPressed variable
 *
 * DEPRECATED
 */

int authentication::getPress(){
    return buttonPressed;
}

/*
 *
 * The accept function will register when the OK button is pressed, and will begin to handle
 * Standard String encryption and compare values from the database and text fields.
 *
 *
 */
void authentication::accept(){
    QSqlQuery query;
     query.exec("SELECT * FROM authentication WHERE username = '"+ui->usernameLineEdit->text()+"'");
     query.last();


      encryptionHandler e;
      QString dec = e.decryptString(query.value(2).toString());
     if(!query.value(1).isNull() && query.value(1).toString() == ui->usernameLineEdit->text()){
         if(ui->usernameLineEdit->text() == "" || ui->usernameLineEdit->text() == " "){
             ui->authenticationStatusLabel->setText("Invalid Username/Password!");
             buttonPressed = 0;
             return;
         }
         qDebug() << "Success on username";
         if(dec == ui->passwordLineEdit->text()){
             qDebug() << "Success on password";
             ui->authenticationStatusLabel->setText("");
              buttonPressed = 1;
              writeToLog("userauthtrue",QDate::currentDate().toString()+" at "+QTime::currentTime().toString()+": User "+ui->usernameLineEdit->text()+" was successfully logged in");
              this->hide();

         }
         else{
             qDebug() << "invalid password";
             ui->authenticationStatusLabel->setText("Invalid Password!");
             writeToLog("userauthtrue",QDate::currentDate().toString()+" at "+QTime::currentTime().toString()+": User "+ui->usernameLineEdit->text()+" was successfully logged in");
             buttonPressed = 0;
         }
     }
     else{
         qDebug() << "invalid username!/password" << ui->usernameLineEdit->text();
         ui->authenticationStatusLabel->setText("Invalid Username/Password!");
         buttonPressed = 0;
     }
}
/*
 *
 * What happens when the cancel button is pushed: the app exits
 *
 *
 */

void authentication::reject(){
    qDebug() << "rejected";
    buttonPressed=0;
    qApp->exit();
}

/*
 * Returns the user description.
 *
 */

QString authentication::getUserDescription(){
    QSqlQuery query;
     query.exec("SELECT * FROM authentication WHERE username = '"+ui->usernameLineEdit->text()+"'");
     query.last();
    return query.value(3).toString();
}


bool authentication::isAccepted(){
    return isAcceptedTrueOrFalseValue;
}







